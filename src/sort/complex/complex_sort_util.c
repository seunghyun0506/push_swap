/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 06:32:51 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 06:34:27 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap_sort.h"
#include "push_swap_stat.h"

void		find_pivot(t_push_swap_stat *stat, t_stack *s,
				int size, int *pivots);
void		partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_part *part);
void		partition_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_part *part);
void		rewind_stack(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				int *sizes);

static void	op_push(t_push_swap_stat *stat, t_stack *from, t_stack *to,
				t_op op_type);
static void	op_rot(t_push_swap_stat *stat, t_stack *s, t_op op_type, int dir);

void	partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_part *part)
{
	int	pivots[2];

	part->cnt[0] = 0;
	part->cnt[1] = 0;
	part->cnt[2] = 0;
	find_pivot(stat, s1, part->size, pivots);
	while (part->size--)
	{
		if (s1->datas[s1->top_index] >= pivots[1])
		{
			op_rot(stat, s1, OP_RA, 0);
			part->cnt[0]++;
		}
		else
		{
			op_push(stat, s1, s2, OP_PB);
			part->cnt[2]++;
			if (s2->datas[s2->top_index] >= pivots[0])
			{
				op_rot(stat, s2, OP_RB, 0);
				part->cnt[1]++;
			}
		}
	}
}

void	partition_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_part *part)
{
	int	pivots[2];

	part->cnt[0] = 0;
	part->cnt[1] = 0;
	part->cnt[2] = 0;
	find_pivot(stat, s2, part->size, pivots);
	while (part->size--)
	{
		if (s2->datas[s2->top_index] < pivots[0])
		{
			op_rot(stat, s2, OP_RB, 0);
			part->cnt[2]++;
		}
		else
		{
			op_push(stat, s2, s1, OP_PA);
			part->cnt[0]++;
			if (s1->datas[s1->top_index] < pivots[1])
			{
				op_rot(stat, s1, OP_RA, 0);
				part->cnt[1]++;
			}
		}
	}
}

void	rewind_stack(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			int *sizes)
{
	t_op	op;

	if (get_stack_size(s1) == sizes[0])
		sizes[0] = 0;
	if (get_stack_size(s2) == sizes[1])
		sizes[1] = 0;
	while (sizes[0] && sizes[1])
	{
		op = OP_RRR;
		rrotate_stacks(s1, s2, &op);
		store_op(stat->op_buffer, op);
		sizes[0]--;
		sizes[1]--;
	}
	while (sizes[0]--)
		op_rot(stat, s1, OP_RRA, 1);
	while (sizes[1]--)
		op_rot(stat, s2, OP_RRB, 1);
}

static void	op_push(t_push_swap_stat *stat, t_stack *from, t_stack *to,
				t_op op_type)
{
	t_op	op;

	op = op_type;
	push_stack(from, to, &op);
	store_op(stat->op_buffer, op);
}

static void	op_rot(t_push_swap_stat *stat, t_stack *s, t_op op_type, int dir)
{
	t_op	op;

	op = op_type;
	if (dir == 0)
		rotate_stack(s, &op);
	else
		rrotate_stack(s, &op);
	store_op(stat->op_buffer, op);
}
