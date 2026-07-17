/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_return.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 00:08:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/18 00:08:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static int	get_rank(int *sorted, int n, int val)
{
	int	left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (sorted[mid] == val) return (mid);
		if (sorted[mid] < val) left = mid + 1;
		else right = mid - 1;
	}
	return (-1);
}

static int	get_chunk_idx(int rank, int chunk_size, int total_chunks)
{
	int	idx = rank / chunk_size;
	if (idx >= total_chunks) idx = total_chunks - 1;
	return (idx);
}

void	execute_move(t_push_swap_stat *stat, t_cost *cost)
{
	int	shared, i;

	if (cost->type == 0)
	{
		shared = cost->cost_a < cost->cost_b ? cost->cost_a : cost->cost_b;
		for (i = 0; i < shared; i++)
			(rotate_stack(stat->stack_a), rotate_stack(stat->stack_b));
		for (i = 0; i < cost->cost_a - shared; i++) rotate_stack(stat->stack_a);
		for (i = 0; i < cost->cost_b - shared; i++) rotate_stack(stat->stack_b);
	}
	else if (cost->type == 1)
	{
		shared = cost->cost_a < cost->cost_b ? cost->cost_a : cost->cost_b;
		for (i = 0; i < shared; i++)
			(rrotate_stack(stat->stack_a), rrotate_stack(stat->stack_b));
		for (i = 0; i < cost->cost_a - shared; i++) rrotate_stack(stat->stack_a);
		for (i = 0; i < cost->cost_b - shared; i++) rrotate_stack(stat->stack_b);
	}
	else if (cost->type == 2)
	{
		for (i = 0; i < cost->cost_a; i++) rotate_stack(stat->stack_a);
		for (i = 0; i < cost->cost_b; i++) rrotate_stack(stat->stack_b);
	}
	else if (cost->type == 3)
	{
		for (i = 0; i < cost->cost_a; i++) rrotate_stack(stat->stack_a);
		for (i = 0; i < cost->cost_b; i++) rotate_stack(stat->stack_b);
	}
	push_stack(stat->stack_b, stat->stack_a);
}

void	align_stack_a(t_stack *a)
{
	int	size = get_stack_size(a);
	int	min_val, min_idx = 0, cur_idx, i;

	if (size <= 1) return ;
	cur_idx = a->top_index;
	min_val = a->datas[cur_idx];
	for (i = 0; i < size; i++)
	{
		if (a->datas[cur_idx] < min_val)
		{
			min_val = a->datas[cur_idx];
			min_idx = i;
		}
		cur_idx = prev_idx(a, cur_idx);
	}
	if (min_idx <= size / 2)
		for (i = 0; i < min_idx; i++) rotate_stack(a);
	else
		for (i = 0; i < size - min_idx; i++) rrotate_stack(a);
}

void	return_to_a_by_chunk(t_push_swap_stat *stat, int chunk_size, int total_chunks)
{
	int		target, len_a, len_b, i, cur, val, rank, c_idx, pos_a, found, total, min_total;
	t_cost	cur_cost, best_cost;
	int		total_n = get_stack_size(stat->stack_a) + get_stack_size(stat->stack_b);

	for (target = total_chunks - 1; target >= 0; target--)
	{
		while (1)
		{
			len_b = get_stack_size(stat->stack_b);
			if (len_b == 0) break ;
			len_a = get_stack_size(stat->stack_a);
			cur = stat->stack_b->top_index;
			found = 0;
			min_total = 2147483647;
			for (i = 0; i < len_b; i++)
			{
				val = stat->stack_b->datas[cur];
				rank = get_rank(stat->sorted, total_n, val);
				c_idx = get_chunk_idx(rank, chunk_size, total_chunks);
				if (c_idx == target)
				{
					pos_a = get_insert_pos_a(stat->stack_a, val);
					calculate_move_cost(i, len_b, pos_a, len_a, &cur_cost);
					if (cur_cost.type == 0 || cur_cost.type == 1)
						total = cur_cost.cost_a > cur_cost.cost_b ? cur_cost.cost_a : cur_cost.cost_b;
					else
						total = cur_cost.cost_a + cur_cost.cost_b;
					if (total < min_total)
					{
						min_total = total;
						best_cost = cur_cost;
						found = 1;
					}
				}
				cur = prev_idx(stat->stack_b, cur);
			}
			if (!found) break ;
			execute_move(stat, &best_cost);
		}
	}
	align_stack_a(stat->stack_a);
}
