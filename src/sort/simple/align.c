/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:42:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:45:02 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static void	align_helper(t_push_swap_stat *stat, int min_idx, int size)
{
	int		i;
	t_op	op;

	i = 0;
	if (min_idx <= size / 2)
	{
		while (i++ < min_idx)
		{
			op = OP_RA;
			if (rotate_stack(stat->stack_a, &op))
				store_op(stat->op_buffer, op);
		}
	}
	else
	{
		while (i++ < size - min_idx)
		{
			op = OP_RRA;
			if (rrotate_stack(stat->stack_a, &op))
				store_op(stat->op_buffer, op);
		}
	}
}

void	align_stack_a(t_push_swap_stat *stat)
{
	int	size;
	int	min_val;
	int	min_idx;
	int	cur_idx;
	int	i;

	size = get_stack_size(stat->stack_a);
	if (size <= 1)
		return ;
	cur_idx = stat->stack_a->top_index;
	min_val = stat->stack_a->datas[cur_idx];
	min_idx = 0;
	i = 0;
	while (i < size)
	{
		if (stat->stack_a->datas[cur_idx] < min_val)
		{
			min_val = stat->stack_a->datas[cur_idx];
			min_idx = i;
		}
		cur_idx = prev_idx(stat->stack_a, cur_idx);
		i++;
	}
	align_helper(stat, min_idx, size);
}

void	align_a(t_push_swap_stat *stat)
{
	align_stack_a(stat);
}
