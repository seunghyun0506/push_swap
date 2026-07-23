/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:44:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"

static void	move_to_b(t_push_swap_stat *stat);
static void	insert_to_a(t_push_swap_stat *stat);

int	simple_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (n <= 1)
		return (1);
	move_to_b(stat);
	if (stat->op_buffer->err)
		return (0);
	insert_to_a(stat);
	if (stat->op_buffer->err)
		return (0);
	align_stack_a(stat);
	if (stat->op_buffer->err)
		return (0);
	return (1);
}

static void	move_to_b(t_push_swap_stat *stat)
{
	while (get_stack_size(stat->stack_a) > 1 && !stat->op_buffer->err)
		op_push(stat, stat->stack_a, stat->stack_b);
}

static void	insert_to_a(t_push_swap_stat *stat)
{
	int	pos_a;
	int	size_a;

	while (get_stack_size(stat->stack_b) > 0 && !stat->op_buffer->err)
	{
		pos_a = get_insert_pos_a(stat->stack_a,
				stat->stack_b->datas[stat->stack_b->top_index]);
		size_a = get_stack_size(stat->stack_a);
		if (pos_a > size_a / 2)
			pos_a -= size_a;
		rotate_n(stat, stat->stack_a, pos_a);
		op_push(stat, stat->stack_b, stat->stack_a);
	}
}
