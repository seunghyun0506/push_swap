/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 06:32:51 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap_sort.h"
#include "push_swap_stat.h"

void	find_pivot(t_push_swap_stat *stat, t_stack *s,
			int size, int *pivots);
void	partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_part *part);
void	partition_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_part *part);
void	rewind_stack(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_pair sizes);

void	partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_part *part)
{
	int	pivots[2];

	part->cnt[0] = 0;
	part->cnt[1] = 0;
	part->cnt[2] = 0;
	find_pivot(stat, s1, part->size, pivots);
	while (part->size-- && !stat->op_buffer->err)
	{
		if (s1->datas[s1->top_index] >= pivots[1])
		{
			op_rotate(stat, s1);
			part->cnt[0]++;
		}
		else
		{
			op_push(stat, s1, s2);
			part->cnt[2]++;
			if (s2->datas[s2->top_index] >= pivots[0])
			{
				op_rotate(stat, s2);
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
	while (part->size-- && !stat->op_buffer->err)
	{
		if (s2->datas[s2->top_index] < pivots[0])
		{
			op_rotate(stat, s2);
			part->cnt[2]++;
		}
		else
		{
			op_push(stat, s2, s1);
			part->cnt[0]++;
			if (s1->datas[s1->top_index] < pivots[1])
			{
				op_rotate(stat, s1);
				part->cnt[1]++;
			}
		}
	}
}

void	rewind_stack(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			t_pair sizes)
{
	if (get_stack_size(s1) == sizes.i)
		sizes.i = 0;
	if (get_stack_size(s2) == sizes.j)
		sizes.j = 0;
	while (sizes.i && sizes.j && !stat->op_buffer->err)
	{
		op_rrotate_stacks(stat, s1, s2);
		sizes.i--;
		sizes.j--;
	}
	while (sizes.i-- && !stat->op_buffer->err)
		op_rrotate(stat, s1);
	while (sizes.j-- && !stat->op_buffer->err)
		op_rrotate(stat, s2);
}
