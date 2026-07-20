/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_divide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:40:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static void	update_match(t_push_swap_stat *stat, t_match *m,
				int c1, int c2);
static int	find_best_rotation_for_pair(t_push_swap_stat *stat,
				int chunk_idx1, int chunk_idx2, int *rot);
static void	push_pair_to_b(t_push_swap_stat *stat, int large_chunk,
				int small_chunk);
static void	rotate_a_n(t_push_swap_stat *stat, int rot);

void	divide_by_chunks(t_push_swap_stat *stat, int chunk_size,
			int total_chunks)
{
	int	num_chunks;
	int	i;

	(void)chunk_size;
	(void)total_chunks;
	num_chunks = get_num_chunks(get_stack_size(stat->stack_a));
	i = 0;
	while (i < num_chunks)
	{
		if (i + 1 < num_chunks)
			push_pair_to_b(stat, i + 1, i);
		else
			push_pair_to_b(stat, i, -1);
		i += 2;
	}
}

static void	update_match(t_push_swap_stat *stat, t_match *m,
				int c1, int c2)
{
	int	rank;

	rank = get_rank(stat->sorted, m->n, stat->stack_a->datas[m->cur]);
	if (is_in_chunk(stat, rank, c1)
		|| (c2 != -1 && is_in_chunk(stat, rank, c2)))
	{
		if (m->first == -1)
			m->first = m->i;
		m->last = m->i;
	}
}

static int	find_best_rotation_for_pair(t_push_swap_stat *stat,
				int chunk_idx1, int chunk_idx2, int *rot)
{
	t_match	m;

	m.size = get_stack_size(stat->stack_a);
	if (m.size == 0)
		return (0);
	m.first = -1;
	m.last = -1;
	m.cur = stat->stack_a->top_index;
	m.i = 0;
	m.n = get_stack_size(stat->stack_a) + get_stack_size(stat->stack_b);
	while (m.i < m.size)
	{
		update_match(stat, &m, chunk_idx1, chunk_idx2);
		m.cur = prev_idx(stat->stack_a, m.cur);
		m.i++;
	}
	if (m.first == -1)
		return (0);
	*rot = m.first;
	if (m.first > m.size - m.last)
		*rot = -(m.size - m.last);
	return (1);
}

static void	push_pair_to_b(t_push_swap_stat *stat, int large_chunk,
				int small_chunk)
{
	int		rot;
	int		i;
	int		val;
	t_op	op;

	while (find_best_rotation_for_pair(stat, large_chunk, small_chunk, &rot))
	{
		rotate_a_n(stat, rot);
		get_stack_top(stat->stack_a, &val);
		i = get_stack_size(stat->stack_a) + get_stack_size(stat->stack_b);
		op = OP_PB;
		push_stack(stat->stack_a, stat->stack_b, &op);
		store_op(stat->op_buffer, op);
		if (!is_in_chunk(stat, get_rank(stat->sorted, i, val), large_chunk)
			&& small_chunk != -1)
		{
			op = OP_RB;
			rotate_stack(stat->stack_b, &op);
			store_op(stat->op_buffer, op);
		}
	}
}

static void	rotate_a_n(t_push_swap_stat *stat, int rot)
{
	int		i;
	t_op	op;

	i = 0;
	if (rot > 0)
	{
		while (i < rot)
		{
			op = OP_RA;
			rotate_stack(stat->stack_a, &op);
			store_op(stat->op_buffer, op);
			i++;
		}
	}
	else
	{
		while (i < -rot)
		{
			op = OP_RRA;
			rrotate_stack(stat->stack_a, &op);
			store_op(stat->op_buffer, op);
			i++;
		}
	}
}
