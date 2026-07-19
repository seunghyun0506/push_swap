/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_return.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 23:59:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static int	is_target_chunk(t_push_swap_stat *stat, int cur_idx,
				int chunk_size, int target_chunk)
{
	int	val;
	int	rank;

	val = stat->stack_b->datas[cur_idx];
	rank = get_rank(stat->sorted, stat->stack_a->capacity, val);
	return (rank / chunk_size == target_chunk);
}

static void	find_best_move(t_push_swap_stat *stat, int chunk_size,
				int target_chunk, t_cost *best_cost)
{
	int		cur_idx;
	int		i;
	int		size;
	t_cost	cost;

	size = get_stack_size(stat->stack_b);
	cur_idx = stat->stack_b->top_index;
	best_cost->cost_a = 10000000;
	best_cost->cost_b = 10000000;
	best_cost->type = 0;
	i = -1;
	while (++i < size)
	{
		if (is_target_chunk(stat, cur_idx, chunk_size, target_chunk))
		{
			calculate_move_cost(stat, get_insert_pos_a(stat->stack_a,
					stat->stack_b->datas[cur_idx]), i, &cost);
			if (calc_total_cost(&cost) < calc_total_cost(best_cost))
				*best_cost = cost;
		}
		cur_idx = prev_idx(stat->stack_b, cur_idx);
	}
}

static void	align_helper(t_push_swap_stat *stat, int min_idx, int size)
{
	int		i;

	i = 0;
	if (min_idx <= size / 2)
	{
		while (i++ < min_idx)
		{
			if (rotate_stack(stat->stack_a))
				store_op(stat->op_buffer, OP_RA);
		}
	}
	else
	{
		while (i++ < size - min_idx)
		{
			if (rrotate_stack(stat->stack_a))
				store_op(stat->op_buffer, OP_RRA);
		}
	}
}

void	align_stack_a(t_push_swap_stat *stat)
{
	int	size;
	int	min_val;
	int	min_idx;
	int	cur_idx;
	int	i;

	size = get_stack_size(stat->stack_a);
	if (size <= 1)
		return ;
	cur_idx = stat->stack_a->top_index;
	min_val = stat->stack_a->datas[cur_idx];
	min_idx = 0;
	i = 0;
	while (i < size)
	{
		if (stat->stack_a->datas[cur_idx] < min_val)
		{
			min_val = stat->stack_a->datas[cur_idx];
			min_idx = i;
		}
		cur_idx = prev_idx(stat->stack_a, cur_idx);
		i++;
	}
	align_helper(stat, min_idx, size);
}

void	return_to_a_by_chunk(t_push_swap_stat *stat, int chunk_size,
			int total_chunks)
{
	int		target_chunk;
	t_cost	best_cost;

	small_sort(stat, stat->stack_a, stat->stack_b,
		get_stack_size(stat->stack_a));
	target_chunk = total_chunks - 1;
	while (target_chunk >= 0)
	{
		while (1)
		{
			best_cost.cost_a = 10000000;
			best_cost.cost_b = 10000000;
			best_cost.type = 0;
			find_best_move(stat, chunk_size, target_chunk, &best_cost);
			if (best_cost.cost_a == 10000000)
				break ;
			execute_move(stat, &best_cost);
		}
		target_chunk--;
	}
	align_stack_a(stat);
}
