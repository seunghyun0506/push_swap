/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:42:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 07:17:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

void		align_stack_a(t_push_swap_stat *stat);
void		align_a(t_push_swap_stat *stat);
static int	find_min_val_idx(t_stack *a, int size);
static void	rotate_to_top(t_push_swap_stat *stat, int min_idx, int size);

void	align_stack_a(t_push_swap_stat *stat)
{
	int	size;
	int	min_idx;

	size = get_stack_size(stat->stack_a);
	if (size <= 1)
		return ;
	min_idx = find_min_val_idx(stat->stack_a, size);
	rotate_to_top(stat, min_idx, size);
}

void	align_a(t_push_swap_stat *stat)
{
	align_stack_a(stat);
}

static int	find_min_val_idx(t_stack *a, int size)
{
	int	min_val;
	int	min_idx;
	int	cur_idx;
	int	i;

	cur_idx = a->top_index;
	min_val = a->datas[cur_idx];
	min_idx = 0;
	i = 0;
	while (i < size)
	{
		if (a->datas[cur_idx] < min_val)
		{
			min_val = a->datas[cur_idx];
			min_idx = i;
		}
		cur_idx = prev_idx(a, cur_idx);
		i++;
	}
	return (min_idx);
}

static void	rotate_to_top(t_push_swap_stat *stat, int min_idx, int size)
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
