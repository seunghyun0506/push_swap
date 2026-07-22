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

typedef struct s_match
{
	int	first;
	int	last;
	int	cur;
	int	i;
	int	size;
	int	n;
}	t_match;

static void	update_match(t_push_swap_stat *stat, t_match *match,
				int chunk_idx1, int chunk_idx2);
static int	find_best_rotation_for_pair(t_push_swap_stat *stat,
				int chunk_idx1, int chunk_idx2, int *rot);
static void	push_pair_to_b(t_push_swap_stat *stat, int inner_chunk,
				int outer_chunk);
static void	rotate_a_n(t_push_swap_stat *stat, int rot);

/*
** Process chunk pairs from the center toward both ends.
** Seven chunks become (2, 3), (1, 4), (0, 5), then (6).
*/
void	divide_by_chunks(t_push_swap_stat *stat)
{
	int	num_chunks;
	int	left_chunk;
	int	right_chunk;

	num_chunks = get_num_chunks(get_stack_size(stat->stack_a));
	left_chunk = num_chunks / 2 - 1;
	right_chunk = left_chunk + 1;
	while (left_chunk >= 0)
	{
		push_pair_to_b(stat, left_chunk, right_chunk);
		left_chunk--;
		right_chunk++;
	}
	if (right_chunk < num_chunks)
		push_pair_to_b(stat, right_chunk, -1);
}

static void	update_match(t_push_swap_stat *stat, t_match *match,
				int chunk_idx1, int chunk_idx2)
{
	int	rank;

	rank = get_rank(stat->sorted, match->n,
			stat->stack_a->datas[match->cur]);
	if (is_in_chunk(stat, rank, chunk_idx1)
		|| (chunk_idx2 != -1 && is_in_chunk(stat, rank, chunk_idx2)))
	{
		if (match->first == -1)
			match->first = match->i;
		match->last = match->i;
	}
}

static int	find_best_rotation_for_pair(t_push_swap_stat *stat,
				int chunk_idx1, int chunk_idx2, int *rot)
{
	t_match	match;

	match.size = get_stack_size(stat->stack_a);
	if (match.size == 0)
		return (0);
	match.first = -1;
	match.last = -1;
	match.cur = stat->stack_a->top_index;
	match.i = 0;
	match.n = get_stack_size(stat->stack_a)
		+ get_stack_size(stat->stack_b);
	while (match.i < match.size)
	{
		update_match(stat, &match, chunk_idx1, chunk_idx2);
		match.cur = prev_idx(stat->stack_a, match.cur);
		match.i++;
	}
	if (match.first == -1)
		return (0);
	*rot = match.first;
	if (match.first > match.size - match.last)
		*rot = -(match.size - match.last);
	return (1);
}

static void	push_pair_to_b(t_push_swap_stat *stat, int inner_chunk,
				int outer_chunk)
{
	int		rot;
	int		total_size;
	int		val;
	t_op	op;

	while (find_best_rotation_for_pair(stat, inner_chunk, outer_chunk, &rot))
	{
		rotate_a_n(stat, rot);
		get_stack_top(stat->stack_a, &val);
		total_size = get_stack_size(stat->stack_a)
			+ get_stack_size(stat->stack_b);
		op = OP_PB;
		push_stack(stat->stack_a, stat->stack_b, &op);
		store_op(stat->op_buffer, op);
		if (outer_chunk != -1
			&& !is_in_chunk(stat,
				get_rank(stat->sorted, total_size, val), outer_chunk))
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
