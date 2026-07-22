/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 12:30:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/22 12:40:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
#include "libft.h"

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

int	get_num_chunks(int n)
{
	int	chunk_size;

	chunk_size = (int)ft_sqrt((double)n);
	if (chunk_size == 0)
		chunk_size = 1;
	return ((n + chunk_size - 1) / chunk_size);
}

int	is_in_chunk(t_push_swap_stat *stat, int val, int chunk_idx)
{
	int	num_chunks;
	int	chunk_size;
	int	limit;
	int	rank;
	int	n;

	if (chunk_idx < 0)
		return (0);
	n = stat->stack_a->capacity;
	rank = get_rank(stat->sorted, n, val);
	num_chunks = get_num_chunks(n);
	chunk_size = (n + num_chunks - 1) / num_chunks;
	if (n >= 6)
		limit = n - 3;
	else
		limit = n;
	if (chunk_idx == num_chunks - 1)
		return (rank >= chunk_idx * chunk_size && rank < limit);
	return (rank >= chunk_idx * chunk_size
		&& rank < (chunk_idx + 1) * chunk_size);
}

void	rotate_n(t_push_swap_stat *stat, t_stack *s, int rot)
{
	t_op	op;

	while (rot > 0)
	{
		op = OP_RA;
		if (s == stat->stack_b)
			op = OP_RB;
		rotate_stack(s, &op);
		store_op(stat->op_buffer, op);
		rot--;
	}
	while (rot < 0)
	{
		op = OP_RRA;
		if (s == stat->stack_b)
			op = OP_RRB;
		rrotate_stack(s, &op);
		store_op(stat->op_buffer, op);
		rot++;
	}
}

int	find_max_chunk_idx(t_push_swap_stat *stat, int chunk_idx)
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
		if (is_in_chunk(stat, stat->stack_b->datas[cur], chunk_idx)
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
