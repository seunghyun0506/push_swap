/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 05:30:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
#include "libft.h"

void		divide_by_chunks(t_push_swap_stat *stat);
void		selection_sort_to_b(t_push_swap_stat *stat);
int			get_num_chunks(int n);
int			is_in_chunk(t_push_swap_stat *stat, int val, int chunk_idx);
int			get_chunk_cnt(t_push_swap_stat *stat, int chunk_idx, int c_sz);

static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2, int c_sz);

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;

	n =stat->element_cnt;
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
		push_pair_to_b(stat, right_chunk, -1, chunk_size);
}

void	selection_sort_to_b(t_push_swap_stat *stat)
{
	int		idx;
	int		sz;
	t_op	op;

	while (get_stack_size(stat->stack_b) > 0 && !stat->op_buffer->err)
	{
		idx = find_max_idx_stack(stat->stack_b);
		sz = get_stack_size(stat->stack_b);
		if (idx > sz / 2)
			idx -= sz;
		rotate_n(stat, stat->stack_b, idx);
		op = OP_PA;
		push_stack(stat->stack_b, stat->stack_a, &op);
		store_op(stat->op_buffer, op);
	}
}

static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2, int c_sz)
{
	int		target_b;
	int		val;
	t_op	op;

	target_b = get_stack_size(stat->stack_b)
		+ get_chunk_cnt(stat, c1, c_sz)
		+ get_chunk_cnt(stat, c2, c_sz);
	while (!stat->op_buffer->err && get_stack_size(stat->stack_b) < target_b)
	{
		get_stack_top(stat->stack_a, &val);
		if (is_in_chunk(stat, val, c1))
		{
			op = OP_PB;
			push_stack(stat->stack_a, stat->stack_b, &op);
			store_op(stat->op_buffer, op);
		}
		else if (c2 != -1 && is_in_chunk(stat, val, c2))
		{
			op = OP_PB;
			push_stack(stat->stack_a, stat->stack_b, &op);
			store_op(stat->op_buffer, op);
			op = OP_RB;
			rotate_stack(stat->stack_b, &op);
			store_op(stat->op_buffer, op);
		}
		else
		{
			op = OP_RA;
			rotate_stack(stat->stack_a, &op);
			store_op(stat->op_buffer, op);
		}
	}
}
