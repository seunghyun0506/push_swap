/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:02:29 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 06:34:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"

static void	op_swap(t_push_swap_stat *stat, t_stack *s, t_op op_type);
static void	op_rotate_s(t_push_swap_stat *stat, t_stack *s, t_op op_type);
static void	three_sort_asc_dispatch(t_push_swap_stat *stat, t_stack *s1);

void	three_sort_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2)
{
	int	t;
	int	m;
	int	b;

	(void)s2;
	if (get_stack_size(s1) < 3)
		return ;
	t = s1->datas[s1->top_index];
	m = s1->datas[prev_idx(s1, s1->top_index)];
	b = s1->datas[prev_idx(s1, prev_idx(s1, s1->top_index))];
	if (t < m && m < b)
		return ;
	three_sort_asc_dispatch(stat, s1);
}

void	three_sort_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2)
{
	int		i;
	t_op	op;

	if (get_stack_size(s2) < 3)
		return ;
	i = 0;
	while (i < 3)
	{
		if (get_stack_size(s2) >= 2 && s2->datas[s2->top_index]
			< s2->datas[prev_idx(s2, s2->top_index)])
			op_swap(stat, s2, OP_SB);
		op = OP_PA;
		push_stack(s2, s1, &op);
		store_op(stat->op_buffer, op);
		i++;
	}
	three_sort_asc(stat, s1, s2);
}

static void	op_swap(t_push_swap_stat *stat, t_stack *s, t_op op_type)
{
	t_op	op;

	op = op_type;
	swap_stack(s, &op);
	store_op(stat->op_buffer, op);
}

static void	op_rotate_s(t_push_swap_stat *stat, t_stack *s, t_op op_type)
{
	t_op	op;

	op = op_type;
	if (op == OP_RA || op == OP_RB)
		rotate_stack(s, &op);
	else
		rrotate_stack(s, &op);
	store_op(stat->op_buffer, op);
}

static void	three_sort_asc_dispatch(t_push_swap_stat *stat, t_stack *s1)
{
	int	t;
	int	m;
	int	b;

	t = s1->datas[s1->top_index];
	m = s1->datas[prev_idx(s1, s1->top_index)];
	b = s1->datas[prev_idx(s1, prev_idx(s1, s1->top_index))];
	if (t < b && b < m)
	{
		op_swap(stat, s1, OP_SA);
		op_rotate_s(stat, s1, OP_RA);
	}
	else if (m < t && t < b)
		op_swap(stat, s1, OP_SA);
	else if (b < t && t < m)
		op_rotate_s(stat, s1, OP_RA);
	else if (m < b && b < t)
		op_rotate_s(stat, s1, OP_RRA);
	else if (b < m && m < t)
	{
		op_swap(stat, s1, OP_SA);
		op_rotate_s(stat, s1, OP_RRA);
	}
}
