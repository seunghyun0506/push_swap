/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_divide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 23:59:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

int	get_rank(int *sorted, int n, int val)
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

static void	find_dists(t_push_swap_stat *stat, t_divide *div)
{
	int	cur_idx;
	int	cur_val;
	int	rank;
	int	i;

	cur_idx = stat->stack_a->top_index;
	div->top_dist = -1;
	i = -1;
	while (++i < div->total_n)
	{
		cur_val = stat->stack_a->datas[cur_idx];
		rank = get_rank(stat->sorted, div->total_n, cur_val);
		if (rank >= div->mid - div->step && rank <= div->mid + div->step)
		{
			if (div->top_dist == -1)
			{
				div->top_dist = i;
				div->bot_dist = i;
			}
			else
				div->bot_dist = i;
		}
		cur_idx = prev_idx(stat->stack_a, cur_idx);
	}
}

static void	move_to_top(t_push_swap_stat *stat, int top_dist, int bot_dist)
{
	int		i;
	int		size;

	size = get_stack_size(stat->stack_a);
	i = 0;
	if (top_dist <= size - bot_dist)
	{
		while (i++ < top_dist)
		{
			if (rotate_stack(stat->stack_a))
				store_op(stat->op_buffer, OP_RA);
		}
	}
	else
	{
		while (i++ < size - bot_dist)
		{
			if (rrotate_stack(stat->stack_a))
				store_op(stat->op_buffer, OP_RRA);
		}
	}
}

static void	do_divide(t_push_swap_stat *stat, t_divide *div)
{
	int		cur;

	while (1)
	{
		find_dists(stat, div);
		if (div->top_dist == -1)
			break ;
		move_to_top(stat, div->top_dist, div->bot_dist);
		get_stack_top(stat->stack_a, &cur);
		cur = get_rank(stat->sorted, div->total_n, cur) / div->chunk_size;
		if (cur >= div->total_chunks)
			cur = div->total_chunks - 1;
		if (push_stack(stat->stack_a, stat->stack_b))
			store_op(stat->op_buffer, OP_PB);
		if (div->step > 0 && cur == div->mid - div->step)
		{
			if (rotate_stack(stat->stack_b))
				store_op(stat->op_buffer, OP_RB);
		}
	}
}

void	divide_by_chunks(t_push_swap_stat *stat, int chunk_size,
			int total_chunks)
{
	t_divide	div;

	div.chunk_size = chunk_size;
	div.total_chunks = total_chunks;
	div.total_n = get_stack_size(stat->stack_a);
	div.mid = total_chunks / 2;
	div.step = 0;
	div.max_step = total_chunks - div.mid;
	if (total_chunks % 2 == 0)
		div.max_step = total_chunks / 2 - 1;
	while (div.step <= div.max_step)
	{
		do_divide(stat, &div);
		div.step++;
	}
	while (get_stack_size(stat->stack_a) > 3)
	{
		div.top_dist = 0;
		div.bot_dist = get_stack_size(stat->stack_a) - 1;
		move_to_top(stat, div.top_dist, div.bot_dist);
		push_stack(stat->stack_a, stat->stack_b);
	}
}
