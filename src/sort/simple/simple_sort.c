/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:44:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 14:55:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
#include "libft.h"
#include <stdlib.h>

static void	rotate_a_n(t_push_swap_stat *stat, int min_rot)
{
	int		i;
	t_op	op;

	i = -1;
	if (min_rot > 0)
	{
		while (++i < min_rot)
		{
			op = OP_RA;
			rotate_stack(stat->stack_a, &op);
			store_op(stat->op_buffer, op);
		}
	}
	else
	{
		while (++i < abs(min_rot))
		{
			op = OP_RRA;
			rrotate_stack(stat->stack_a, &op);
			store_op(stat->op_buffer, op);
		}
	}
}

static void	push_to_b_insertion(t_push_swap_stat *stat)
{
	int		t;
	int		s;
	int		b;
	t_op	op;

	while (get_stack_size(stat->stack_a) > 3)
	{
		t = stat->stack_a->datas[stat->stack_a->top_index];
		s = stat->stack_a->datas[prev_idx(stat->stack_a,
				stat->stack_a->top_index)];
		b = stat->stack_a->datas[next_idx(stat->stack_a,
				stat->stack_a->bottom_index)];
		if (s < t && s < b && swap_stack(stat->stack_a, &op))
			store_op(stat->op_buffer, OP_SA);
		else if (b < t && b < s && rrotate_stack(stat->stack_a, &op))
			store_op(stat->op_buffer, OP_RRA);
		op = OP_PB;
		push_stack(stat->stack_a, stat->stack_b, &op);
		store_op(stat->op_buffer, op);
	}
}

static void	push_to_a_insertion(t_push_swap_stat *stat)
{
	int		pos_a;
	int		size_a;
	t_op	op;

	while (get_stack_size(stat->stack_b) > 0)
	{
		pos_a = get_insert_pos_a(stat->stack_a,
				stat->stack_b->datas[stat->stack_b->top_index]);
		size_a = get_stack_size(stat->stack_a);
		if (pos_a <= size_a / 2)
			rotate_a_n(stat, pos_a);
		else
			rotate_a_n(stat, pos_a - size_a);
		op = OP_PA;
		push_stack(stat->stack_b, stat->stack_a, &op);
		store_op(stat->op_buffer, op);
	}
}

int	simple_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat, stat->stack_a, stat->stack_b, n));
	push_to_b_insertion(stat);
	three_sort_asc(stat, stat->stack_a, stat->stack_b);
	push_to_a_insertion(stat);
	align_a(stat);
	return (1);
}
