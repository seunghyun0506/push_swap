/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/22 16:20:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

void		divide_by_chunks(t_push_swap_stat *stat);
void		selection_sort_to_b(t_push_swap_stat *stat);
int			get_num_chunks(int n);
int			is_in_chunk(t_push_swap_stat *stat, int val, int chunk_idx);
void		rotate_n(t_push_swap_stat *stat, t_stack *s, int rot);
static int	find_best_rot(t_push_swap_stat *stat, int c1, int c2, int *rot);
static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2);

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
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
	int	left_chunk;
	int	right_chunk;

	num_chunks = get_num_chunks(stat->element_cnt);
	left_chunk = num_chunks / 2 - 1;
	right_chunk = left_chunk + 1;
	while (left_chunk >= 0 && !stat->op_buffer->err)
	{
		push_pair_to_b(stat, left_chunk, right_chunk);
		left_chunk--;
		right_chunk++;
	}
	if (right_chunk < num_chunks && !stat->op_buffer->err)
		push_pair_to_b(stat, right_chunk, -1);
}

static void	push_pair_to_b(t_push_swap_stat *stat, int c1, int c2)
{
	int		rot;
	int		val;
	t_op	op;

	while (!stat->op_buffer->err && find_best_rot(stat, c1, c2, &rot))
	{
		rotate_n(stat, stat->stack_a, rot);
		get_stack_top(stat->stack_a, &val);
		op = OP_PB;
		push_stack(stat->stack_a, stat->stack_b, &op);
		store_op(stat->op_buffer, op);
		if (c2 != -1 && !is_in_chunk(stat, val, c2))
		{
			op = OP_RB;
			rotate_stack(stat->stack_b, &op);
			store_op(stat->op_buffer, op);
		}
	}
}

static int	find_best_rot(t_push_swap_stat *stat, int c1, int c2, int *rot)
{
	int	s;
	int	cur;
	int	f;
	int	l;

	f = -1;
	s = -1;
	cur = stat->stack_a->top_index;
	while (++s < get_stack_size(stat->stack_a))
	{
		if (is_in_chunk(stat, stat->stack_a->datas[cur], c1)
			|| is_in_chunk(stat, stat->stack_a->datas[cur], c2))
		{
			if (f == -1)
				f = s;
			l = s;
		}
		cur = prev_idx(stat->stack_a, cur);
	}
	if (f == -1)
		return (0);
	*rot = f;
	if (f > s - l)
		*rot = -(s - l);
	return (1);
}
