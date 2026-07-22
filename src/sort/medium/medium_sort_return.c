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

static int	find_max_chunk_idx(t_push_swap_stat *stat, int chunk_idx,
				int total_size);
static void	rotate_s_n(t_push_swap_stat *stat, t_stack *s, int rot);
static void	push_max_to_a(t_push_swap_stat *stat, int max_idx);

void	return_to_a_by_chunk(t_push_swap_stat *stat)
{
	int		target;
	int		max_idx;
	int		total_size;

	total_size = get_stack_size(stat->stack_a)
		+ get_stack_size(stat->stack_b);
	small_sort(stat, stat->stack_a, stat->stack_b,
		get_stack_size(stat->stack_a));
	target = get_num_chunks(total_size) - 1;
	while (target >= 0)
	{
		while (1)
		{
			max_idx = find_max_chunk_idx(stat, target, total_size);
			if (max_idx == -1)
				break ;
			push_max_to_a(stat, max_idx);
		}
		target--;
	}
}

static int	find_max_chunk_idx(t_push_swap_stat *stat, int chunk_idx,
			int total_size)
{
	int	cur;
	int	max_val;
	int	max_idx;
	int	size;
	int	i;

	size = get_stack_size(stat->stack_b);
	cur = stat->stack_b->top_index;
	max_idx = -1;
	i = 0;
	while (i < size)
	{
		if (is_in_chunk(stat, get_rank(stat->sorted, total_size,
					stat->stack_b->datas[cur]), chunk_idx)
			&& (max_idx == -1 || stat->stack_b->datas[cur] > max_val))
		{
			max_val = stat->stack_b->datas[cur];
			max_idx = i;
		}
		cur = prev_idx(stat->stack_b, cur);
		i++;
	}
	return (max_idx);
}

static void	rotate_s_n(t_push_swap_stat *stat, t_stack *s, int rot)
{
	int		i;
	int		count;
	t_op	op;

	count = rot;
	if (count < 0)
		count = -count;
	i = 0;
	while (i < count)
	{
		if (rot > 0)
		{
			op = OP_RB;
			rotate_stack(s, &op);
		}
		else
		{
			op = OP_RRB;
			rrotate_stack(s, &op);
		}
		store_op(stat->op_buffer, op);
		i++;
	}
}

static void	push_max_to_a(t_push_swap_stat *stat, int max_idx)
{
	int		size_b;
	t_op	op;

	size_b = get_stack_size(stat->stack_b);
	if (max_idx <= size_b / 2)
		rotate_s_n(stat, stat->stack_b, max_idx);
	else
		rotate_s_n(stat, stat->stack_b, max_idx - size_b);
	op = OP_PA;
	push_stack(stat->stack_b, stat->stack_a, &op);
	store_op(stat->op_buffer, op);
}
