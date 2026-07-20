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

static int	find_max_chunk_idx(t_push_swap_stat *stat, int chunk_idx, int n);
static void	rotate_s_n(t_push_swap_stat *stat, t_stack *s, int rot);
static void	push_max_to_a(t_push_swap_stat *stat, int max_idx);

void	return_to_a_by_chunk(t_push_swap_stat *stat, int chunk_size,
			int total_chunks)
{
	int		target;
	int		max_idx;
	int		n;

	(void)chunk_size;
	(void)total_chunks;
	n = get_stack_size(stat->stack_a) + get_stack_size(stat->stack_b);
	small_sort(stat, stat->stack_a, stat->stack_b,
		get_stack_size(stat->stack_a));
	target = get_num_chunks(n) - 1;
	while (target >= 0)
	{
		while (1)
		{
			max_idx = find_max_chunk_idx(stat, target, n);
			if (max_idx == -1)
				break ;
			push_max_to_a(stat, max_idx);
		}
		target--;
	}
}

static int	find_max_chunk_idx(t_push_swap_stat *stat, int chunk_idx, int n)
{
	int	cur;
	int	max[2];
	int	size;
	int	i;

	size = get_stack_size(stat->stack_b);
	cur = stat->stack_b->top_index;
	max[0] = -2147483648;
	max[1] = -1;
	i = -1;
	while (++i < size)
	{
		if (is_in_chunk(stat, get_rank(stat->sorted, n,
					stat->stack_b->datas[cur]), chunk_idx)
			&& stat->stack_b->datas[cur] > max[0])
		{
			max[0] = stat->stack_b->datas[cur];
			max[1] = i;
		}
		cur = prev_idx(stat->stack_b, cur);
	}
	return (max[1]);
}

static void	rotate_s_n(t_push_swap_stat *stat, t_stack *s, int rot)
{
	int		i;
	t_op	op;

	i = -1;
	while (++i < abs(rot))
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
