/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "libft.h"

void		divide_by_chunks(t_push_swap_stat *stat);
void		selection_sort_to_b(t_push_swap_stat *stat);
int			get_num_chunks(int n);
int			is_in_chunk(t_push_swap_stat *stat, int val, int chunk_idx);
int			get_chunk_cnt(t_push_swap_stat *stat, int chunk_idx,
				int chunk_size);

static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2,
				int chunk_size);

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;

	n = stat->element_cnt;
	if (n <= 1)
		return (1);
	divide_by_chunks(stat);
	if (stat->op_buffer->err)
		return (0);
	selection_sort_to_b(stat);
	if (stat->op_buffer->err)
		return (0);
	return (1);
}

void	divide_by_chunks(t_push_swap_stat *stat)
{
	int	num_chunks;
	int	chunk_size;
	int	left_chunk;
	int	right_chunk;

	chunk_size = (int)ft_sqrt((double)stat->element_cnt);
	if (chunk_size == 0)
		chunk_size = 1;
	num_chunks = (stat->element_cnt + chunk_size - 1) / chunk_size;
	left_chunk = num_chunks / 2 - 1;
	right_chunk = left_chunk + 1;
	while (left_chunk >= 0 && !stat->op_buffer->err)
	{
		push_pair_to_b(stat, left_chunk, right_chunk, chunk_size);
		left_chunk--;
		right_chunk++;
	}
	if (right_chunk < num_chunks && !stat->op_buffer->err)
		push_pair_to_b(stat, -1, right_chunk, chunk_size);
}

void	selection_sort_to_b(t_push_swap_stat *stat)
{
	int	idx;
	int	size;

	size = get_stack_size(stat->stack_b);
	while (size > 0 && !stat->op_buffer->err)
	{
		idx = find_max_idx_stack(stat->stack_b);
		if (idx > size / 2)
			idx -= size;
		rotate_n(stat, stat->stack_b, idx);
		op_push(stat, stat->stack_b, stat->stack_a);
		size--;
	}
}

static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2,
				int chunk_size)
{
	int	target_b;
	int	val;

	target_b = get_chunk_cnt(stat, c1, chunk_size)
		+ get_chunk_cnt(stat, c2, chunk_size);
	while (!stat->op_buffer->err && target_b > 0)
	{
		get_stack_top(stat->stack_a, &val);
		if (is_in_chunk(stat, val, c2))
			(op_push(stat, stat->stack_a, stat->stack_b), target_b--);
		else if (c1 >= 0 && is_in_chunk(stat, val, c1))
		{
			op_push(stat, stat->stack_a, stat->stack_b);
			op_rotate(stat, stat->stack_b);
			target_b--;
		}
		else
			op_rotate(stat, stat->stack_a);
	}
}
