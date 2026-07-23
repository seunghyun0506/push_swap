/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_stack_rrotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 10:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort_utils.h"

void	op_rrotate(t_push_swap_stat *stat, t_stack *s)
{
	t_op	op;

	if (!stat || !stat->op_buffer || stat->op_buffer->err)
		return ;
	if (s == stat->stack_a)
		op = OP_RRA;
	else
		op = OP_RRB;
	rrotate_stack(s, &op);
	store_op(stat->op_buffer, op);
}

void	op_rrotate_stacks(t_push_swap_stat *stat, t_stack *s1, t_stack *s2)
{
	t_op	op;

	if (!stat || !stat->op_buffer || stat->op_buffer->err)
		return ;
	op = OP_RRR;
	rrotate_stacks(s1, s2, &op);
	store_op(stat->op_buffer, op);
}
