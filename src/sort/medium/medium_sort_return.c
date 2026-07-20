/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_return.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:42:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
#include <stdlib.h>

static int	is_target_chunk(t_push_swap_stat *stat, int cur_idx,
				int chunk_size, int target_chunk)
{
	int	val;
	int	rank;

	val = stat->stack_b->datas[cur_idx];
	rank = get_rank(stat->sorted, stat->stack_a->capacity, val);
	return (rank / chunk_size == target_chunk);
}

static int	find_max_chunk_idx(t_push_swap_stat *stat, int chunk_size,
				int target_chunk)
{
	int	cur;
	int	max_val;
	int	max_idx;
	int	size;
	int	i;

	size = get_stack_size(stat->stack_b);
	cur = stat->stack_b->top_index;
	max_val = -2147483648;
	max_idx = -1;
	i = 0;
	while (i < size)
	{
		if (is_target_chunk(stat, cur, chunk_size, target_chunk))
		{
			if (stat->stack_b->datas[cur] > max_val)
			{
				max_val = stat->stack_b->datas[cur];
				max_idx = i;
			}
		}
		cur = prev_idx(stat->stack_b, cur);
		i++;
	}
	return (max_idx);
}

static void	rotate_s_n(t_push_swap_stat *stat, t_stack *s, int rot, int is_a)
{
	int		i;
	t_op	op;

	i = -1;
	while (++i < abs(rot))
	{
		if (rot > 0)
		{
			op = OP_RB;
			if (is_a)
				op = OP_RA;
			rotate_stack(s, &op);
		}
		else
		{
			op = OP_RRB;
			if (is_a)
				op = OP_RRA;
			rrotate_stack(s, &op);
		}
		store_op(stat->op_buffer, op);
	}
}

static void	push_next_to_a(t_push_swap_stat *stat, int max_idx)
{
	int		size_b;
	int		pos_a;
	t_op	op;

	size_b = get_stack_size(stat->stack_b);
	if (max_idx <= size_b / 2)
		rotate_s_n(stat, stat->stack_b, max_idx, 0);
	else
		rotate_s_n(stat, stat->stack_b, max_idx - size_b, 0);
	pos_a = get_insert_pos_a(stat->stack_a,
			stat->stack_b->datas[stat->stack_b->top_index]);
	if (pos_a <= get_stack_size(stat->stack_a) / 2)
		rotate_s_n(stat, stat->stack_a, pos_a, 1);
	else
		rotate_s_n(stat, stat->stack_a,
			pos_a - get_stack_size(stat->stack_a), 1);
	op = OP_PA;
	push_stack(stat->stack_b, stat->stack_a, &op);
	store_op(stat->op_buffer, op);
}

void	return_to_a_by_chunk(t_push_swap_stat *stat, int chunk_size,
			int total_chunks)
{
	int		target;
	int		max_idx;

	small_sort(stat, stat->stack_a, stat->stack_b,
		get_stack_size(stat->stack_a));
	target = total_chunks;
	while (--target >= 0)
	{
		while (1)
		{
			max_idx = find_max_chunk_idx(stat, chunk_size, target);
			if (max_idx == -1)
				break ;
			push_next_to_a(stat, max_idx);
		}
	}
	align_stack_a(stat);
}
