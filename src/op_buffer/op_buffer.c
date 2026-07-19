/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:53:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 12:53:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op_buffer.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

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
	return (buffer);
}

void	free_op_buffer(t_op_buffer *buffer)
{
	if (!buffer)
		return ;
	free(buffer->arr);
	free(buffer);
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

static int	resize_op_buffer(t_op_buffer *buffer)
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

void	store_op(t_op_buffer *buffer, t_op op)
{
	t_op	current;
	t_op	top;
	t_op	merged;
	int		action;

	if (!buffer || op == OP_NONE)
		return ;
	current = op;
	while (buffer->idx > 0)
	{
		top = buffer->arr[buffer->idx - 1];
		action = get_action_type(top, current, &merged);
		if (action == 0)
			break ;
		buffer->idx--;
		if (action == 1)
		{
			current = OP_NONE;
			break ;
		}
		current = merged;
	}
	if (current != OP_NONE)
	{
		if (buffer->idx >= buffer->capacity)
		{
			if (!resize_op_buffer(buffer))
				return ;
		}
		buffer->arr[buffer->idx++] = current;
	}
}

void	print_op_buffer(t_op_buffer *buffer)
{
	int			i;
	const char	*names[12];

	if (!buffer || !buffer->arr)
		return ;
	names[OP_NONE] = "";
	names[OP_SA] = "sa\n";
	names[OP_SB] = "sb\n";
	names[OP_SS] = "ss\n";
	names[OP_PA] = "pa\n";
	names[OP_PB] = "pb\n";
	names[OP_RA] = "ra\n";
	names[OP_RB] = "rb\n";
	names[OP_RR] = "rr\n";
	names[OP_RRA] = "rra\n";
	names[OP_RRB] = "rrb\n";
	names[OP_RRR] = "rrr\n";
	i = 0;
	while (i < buffer->idx)
	{
		if (buffer->arr[i] >= OP_SA && buffer->arr[i] <= OP_RRR)
			ft_putstr_fd((char *)names[buffer->arr[i]], 1);
		i++;
	}
}
