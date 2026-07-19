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
#include <stdlib.h>
#include <unistd.h>

t_op_buffer	*init_op_buffer(void)
{
	t_op_buffer	*buffer;

	buffer = (t_op_buffer *)malloc(sizeof(t_op_buffer));
	if (!buffer)
		return (NULL);
	buffer->ops = vecnew(32);
	if (!buffer->ops)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void	free_op_buffer(t_op_buffer *buffer)
{
	if (!buffer)
		return ;
	vecdel(buffer->ops);
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

void	store_op(t_op_buffer *buffer, t_op op)
{
	t_op	current;
	t_op	top;
	t_op	merged;
	int		action;

	if (!buffer || op == OP_NONE)
		return ;
	current = op;
	while (buffer->ops->idx > 0)
	{
		top = (t_op)buffer->ops->arr[buffer->ops->idx - 1];
		action = get_action_type(top, current, &merged);
		if (action == 1)
		{
			vecremove(buffer->ops, buffer->ops->idx - 1);
			current = OP_NONE;
			break ;
		}
		else if (action == 2)
		{
			vecremove(buffer->ops, buffer->ops->idx - 1);
			current = merged;
		}
		else
			break ;
	}
	if (current != OP_NONE)
		vecadd_back(buffer->ops, current);
}

void	print_op_buffer(t_op_buffer *buffer)
{
	int		i;
	t_op	op;

	if (!buffer || !buffer->ops)
		return ;
	i = 0;
	while (i < buffer->ops->idx)
	{
		op = (t_op)buffer->ops->arr[i];
		if (op == OP_SA)
			write(1, "sa\n", 3);
		else if (op == OP_SB)
			write(1, "sb\n", 3);
		else if (op == OP_SS)
			write(1, "ss\n", 3);
		else if (op == OP_PA)
			write(1, "pa\n", 3);
		else if (op == OP_PB)
			write(1, "pb\n", 3);
		else if (op == OP_RA)
			write(1, "ra\n", 3);
		else if (op == OP_RB)
			write(1, "rb\n", 3);
		else if (op == OP_RR)
			write(1, "rr\n", 3);
		else if (op == OP_RRA)
			write(1, "rra\n", 4);
		else if (op == OP_RRB)
			write(1, "rrb\n", 4);
		else if (op == OP_RRR)
			write(1, "rrr\n", 4);
		i++;
	}
}
