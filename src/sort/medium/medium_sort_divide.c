/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_divide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 00:03:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/18 00:03:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static int	get_rank(int *sorted, int n, int val)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (sorted[mid] == val)
			return (mid);
		if (sorted[mid] < val)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}

static int	get_chunk_idx(int rank, int chunk_size, int total_chunks)
{
	int	idx;

	idx = rank / chunk_size;
	if (idx >= total_chunks)
		idx = total_chunks - 1;
	return (idx);
}

static int	is_target(int chunk_idx, int step, int mid, int total_chunks)
{
	if (step == 0)
		return (chunk_idx == mid);
	if (mid - step >= 0 && chunk_idx == mid - step)
		return (1);
	if (mid + step < total_chunks && chunk_idx == mid + step)
		return (1);
	return (0);
}

static void	execute_push(t_push_swap_stat *stat, int chunk_idx, int step, int mid)
{
	push_stack(stat->stack_a, stat->stack_b);
	if (step > 0 && chunk_idx == mid - step)
		rotate_stack(stat->stack_b);
}

void	divide_by_chunks(t_push_swap_stat *stat, int chunk_size, int total_chunks)
{
	int	mid = total_chunks / 2;
	int	max_step = mid;
	int	step, i, size, top_dist, bot_dist, cur_idx, rank, chunk_idx;
	int	total_n = get_stack_size(stat->stack_a);

	if (total_chunks - 1 - mid > max_step)
		max_step = total_chunks - 1 - mid;
	for (step = 0; step <= max_step; step++)
	{
		while (1)
		{
			size = get_stack_size(stat->stack_a);
			top_dist = -1;
			bot_dist = -1;
			cur_idx = stat->stack_a->top_index;
			for (i = 0; i < size; i++)
			{
				rank = get_rank(stat->sorted, total_n, stat->stack_a->datas[cur_idx]);
				chunk_idx = get_chunk_idx(rank, chunk_size, total_chunks);
				if (is_target(chunk_idx, step, mid, total_chunks))
				{
					if (top_dist == -1)
						top_dist = i;
					bot_dist = i;
				}
				cur_idx = prev_idx(stat->stack_a, cur_idx);
			}
			if (top_dist == -1)
				break ;
			if (top_dist <= size - bot_dist)
			{
				for (i = 0; i < top_dist; i++)
					rotate_stack(stat->stack_a);
			}
			else
			{
				for (i = 0; i < size - bot_dist; i++)
					rrotate_stack(stat->stack_a);
			}
			get_stack_top(stat->stack_a, &cur_idx);
			rank = get_rank(stat->sorted, total_n, cur_idx);
			chunk_idx = get_chunk_idx(rank, chunk_size, total_chunks);
			execute_push(stat, chunk_idx, step, mid);
		}
	}
}
