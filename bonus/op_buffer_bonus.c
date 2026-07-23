/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 11:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_buffer_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static int	resize(t_op_buffer *buffer);

t_op_buffer	*init_op_buffer(void)
{
	t_op_buffer	*buffer;

	buffer = (t_op_buffer *)malloc(sizeof(t_op_buffer));
	if (!buffer)
		return (NULL);
	buffer->arr = (t_op *)malloc(sizeof(t_op) * 32);
	if (!buffer->arr)
	{
		free(buffer);
		return (NULL);
	}
	buffer->idx = 0;
	buffer->capacity = 32;
	buffer->err = 0;
	return (buffer);
}

static int	get_action_type(t_op top, t_op cur, t_op *merged)
{
	if ((top == OP_RA && cur == OP_RRA) || (top == OP_RRA && cur == OP_RA)
		|| (top == OP_RB && cur == OP_RRB) || (top == OP_RRB && cur == OP_RB)
		|| (top == OP_PA && cur == OP_PB) || (top == OP_PB && cur == OP_PA)
		|| (top == OP_SA && cur == OP_SA) || (top == OP_SB && cur == OP_SB)
		|| (top == OP_RR && cur == OP_RRR) || (top == OP_RRR && cur == OP_RR)
		|| (top == OP_SS && cur == OP_SS))
		return (1);
	if ((top == OP_RA && cur == OP_RB) || (top == OP_RB && cur == OP_RA))
	{
		*merged = OP_RR;
		return (2);
	}
	if ((top == OP_RRA && cur == OP_RRB) || (top == OP_RRB && cur == OP_RRA))
	{
		*merged = OP_RRR;
		return (2);
	}
	if ((top == OP_SA && cur == OP_SB) || (top == OP_SB && cur == OP_SA))
	{
		*merged = OP_SS;
		return (2);
	}
	return (0);
}

void	store_op(t_op_buffer *buffer, t_op op)
{
	t_op	merged;
	int		act;

	if (!buffer || buffer->err || op == OP_NONE)
		return ;
	while (buffer->idx > 0)
	{
		act = get_action_type(buffer->arr[buffer->idx - 1], op, &merged);
		if (act == 0)
			break ;
		buffer->idx--;
		if (act == 1)
		{
			op = OP_NONE;
			break ;
		}
		op = merged;
	}
	if (op == OP_NONE)
		return ;
	if (buffer->idx >= buffer->capacity && !resize(buffer))
		return ((void)(buffer->err = 1));
	buffer->arr[buffer->idx++] = op;
}

static int	resize(t_op_buffer *buffer)
{
	t_op	*new_arr;
	int		i;

	buffer->capacity *= 2;
	new_arr = (t_op *)malloc(sizeof(t_op) * buffer->capacity);
	if (!new_arr)
		return (0);
	i = 0;
	while (i < buffer->idx)
	{
		new_arr[i] = buffer->arr[i];
		i++;
	}
	free(buffer->arr);
	buffer->arr = new_arr;
	return (1);
}

void	free_op_buffer(t_op_buffer *buffer)
{
	if (!buffer)
		return ;
	free(buffer->arr);
	free(buffer);
}
