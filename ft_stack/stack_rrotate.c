/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rrotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 10:48:57 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 18:12:57 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"

int	rrotate_stack(t_stack *s, t_op *op)
{
	int	next_top;
	int	next_bottom;

	if (get_stack_size(s) <= 1)
	{
		if (op)
			*op = OP_NONE;
		return (0);
	}
	next_top = next_idx(s, s->top_index);
	next_bottom = next_idx(s, s->bottom_index);
	s->datas[next_top] = s->datas[next_bottom];
	s->top_index = next_top;
	s->bottom_index = next_bottom;
	return (1);
}

int	rrotate_stacks(t_stack *s1, t_stack *s2, t_op *op)
{
	if (get_stack_size(s1) <= 1 || get_stack_size(s2) <= 1)
	{
		if (op)
			*op = OP_NONE;
		return (0);
	}
	rrotate_stack(s1, 0);
	rrotate_stack(s2, 0);
	return (1);
}
