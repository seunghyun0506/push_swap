/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_stack_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 10:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort_utils.h"

void	op_rotate(t_push_swap_stat *stat, t_stack *s)
{
	t_op	op;

	if (!stat || !stat->op_buffer || stat->op_buffer->err)
		return ;
	if (s == stat->stack_a)
		op = OP_RA;
	else
		op = OP_RB;
	rotate_stack(s, &op);
	store_op(stat->op_buffer, op);
}
