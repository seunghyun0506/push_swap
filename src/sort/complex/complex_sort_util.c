/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 06:32:51 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 19:29:50 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"
#include "push_swap_stat.h"

void		find_pivot(t_stack *s, int size, int *pivot1, int *pivot2);
void		partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_part *part);
void		partition_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_part *part);
void		rewind_stack(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				int *sizes);

static void	op_push(t_push_swap_stat *stat, t_stack *from, t_stack *to,
				t_op op_type)
{
	if (push_stack(from, to))
		store_op(stat->op_buffer, op_type);
}

static void	op_rot(t_push_swap_stat *stat, t_stack *s, t_op op_type, int dir)
{
	if (dir == 0)
	{
		if (rotate_stack(s))
			store_op(stat->op_buffer, op_type);
	}
	else
	{
		if (rrotate_stack(s))
			store_op(stat->op_buffer, op_type);
	}
}

void	partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_part *part)
{
	int	pivot1;
	int	pivot2;

	part->cnt[0] = 0;
	part->cnt[1] = 0;
	part->cnt[2] = 0;
	find_pivot(s1, part->size, &pivot1, &pivot2);
	while (part->size--)
	{
		if (s1->datas[s1->top_index] >= pivot2)
		{
			op_rot(stat, s1, OP_RA, 0);
			part->cnt[0]++;
		}
		else
		{
			op_push(stat, s1, s2, OP_PB);
			part->cnt[2]++;
			if (s2->datas[s2->top_index] >= pivot1)
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
	int	pivot1;
	int	pivot2;

	part->cnt[0] = 0;
	part->cnt[1] = 0;
	part->cnt[2] = 0;
	find_pivot(s2, part->size, &pivot1, &pivot2);
	while (part->size--)
	{
		if (s2->datas[s2->top_index] < pivot1)
		{
			op_rot(stat, s2, OP_RB, 0);
			part->cnt[2]++;
		}
		else
		{
			op_push(stat, s2, s1, OP_PA);
			part->cnt[0]++;
			if (s1->datas[s1->top_index] < pivot2)
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
	if (get_stack_size(s1) == sizes[0])
		sizes[0] = 0;
	if (get_stack_size(s2) == sizes[1])
		sizes[1] = 0;
	while (sizes[0] && sizes[1])
	{
		if (rrotate_stacks(s1, s2))
			store_op(stat->op_buffer, OP_RRR);
		sizes[0]--;
		sizes[1]--;
	}
	while (sizes[0]--)
		op_rot(stat, s1, OP_RRA, 1);
	while (sizes[1]--)
		op_rot(stat, s2, OP_RRB, 1);
}
