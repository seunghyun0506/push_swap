/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/22 16:20:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static int	find_best_rot(t_push_swap_stat *stat, int c1, int c2, int *rot);
static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2);

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat, stat->stack_a, stat->stack_b, n));
	divide_by_chunks(stat);
	return_to_a_by_chunk(stat);
	return (1);
}

void	divide_by_chunks(t_push_swap_stat *stat)
{
	int	num_chunks;
	int	left_chunk;
	int	right_chunk;

	num_chunks = get_num_chunks(get_stack_size(stat->stack_a));
	left_chunk = num_chunks / 2 - 1;
	right_chunk = left_chunk + 1;
	while (left_chunk >= 0)
	{
		push_pair_to_b(stat, left_chunk, right_chunk);
		left_chunk--;
		right_chunk++;
	}
	if (right_chunk < num_chunks)
		push_pair_to_b(stat, right_chunk, -1);
}

void	return_to_a_by_chunk(t_push_swap_stat *stat)
{
	int		target;
	int		idx;
	int		sz;
	t_op	op;

	small_sort(stat, stat->stack_a, stat->stack_b,
		get_stack_size(stat->stack_a));
	target = get_num_chunks(stat->stack_a->capacity) - 1;
	while (target >= 0)
	{
		idx = find_max_chunk_idx(stat, target);
		while (idx != -1)
		{
			sz = get_stack_size(stat->stack_b);
			if (idx > sz / 2)
				idx -= sz;
			rotate_n(stat, stat->stack_b, idx);
			op = OP_PA;
			push_stack(stat->stack_b, stat->stack_a, &op);
			store_op(stat->op_buffer, op);
			idx = find_max_chunk_idx(stat, target);
		}
		target--;
	}
}

static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2)
{
	int		rot;
	int		val;
	t_op	op;

	while (find_best_rot(stat, c1, c2, &rot))
	{
		rotate_n(stat, stat->stack_a, rot);
		get_stack_top(stat->stack_a, &val);
		op = OP_PB;
		push_stack(stat->stack_a, stat->stack_b, &op);
		store_op(stat->op_buffer, op);
		if (c2 != -1 && !is_in_chunk(stat, val, c2))
		{
			op = OP_RB;
			rotate_stack(stat->stack_b, &op);
			store_op(stat->op_buffer, op);
		}
	}
}

static int	find_best_rot(t_push_swap_stat *stat, int c1, int c2, int *rot)
{
	int	s;
	int	cur;
	int	f;
	int	l;

	f = -1;
	s = -1;
	cur = stat->stack_a->top_index;
	while (++s < get_stack_size(stat->stack_a))
	{
		if (is_in_chunk(stat, stat->stack_a->datas[cur], c1)
			|| is_in_chunk(stat, stat->stack_a->datas[cur], c2))
		{
			if (f == -1)
				f = s;
			l = s;
		}
		cur = prev_idx(stat->stack_a, cur);
	}
	if (f == -1)
		return (0);
	*rot = f;
	if (f > s - l)
		*rot = -(s - l);
	return (1);
}
