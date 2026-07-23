/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 10:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort_utils.h"

void	op_push(t_push_swap_stat *stat, t_stack *from, t_stack *to)
{
	t_op	op;

	if (!stat || !stat->op_buffer || stat->op_buffer->err)
		return ;
	if (from == stat->stack_a)
		op = OP_PB;
	else
		op = OP_PA;
	push_stack(from, to, &op);
	store_op(stat->op_buffer, op);
}
