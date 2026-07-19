/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 16:02:29 by slim              #+#    #+#             */
/*   Updated: 2026/07/13 19:45:23 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"

static void	op_push(t_push_swap_stat *stat, t_stack *from, t_stack *to,
				t_op op_type)
{
	if (push_stack(from, to))
		store_op(stat->op_buffer, op_type);
}

static void	op_swap(t_push_swap_stat *stat, t_stack *s, t_op op_type)
{
	if (swap_stack(s))
		store_op(stat->op_buffer, op_type);
}

static void	three_sort_asc_cases(t_push_swap_stat *stat, t_stack *s1,
				t_stack *s2, int case_id)
{
	if (case_id == 1 || case_id == 3)
	{
		op_push(stat, s1, s2, OP_PB);
		op_swap(stat, s1, OP_SA);
		op_push(stat, s2, s1, OP_PA);
		if (case_id == 3)
			op_swap(stat, s1, OP_SA);
	}
	else if (case_id == 2)
		op_swap(stat, s1, OP_SA);
	else
	{
		op_swap(stat, s1, OP_SA);
		op_push(stat, s1, s2, OP_PB);
		op_swap(stat, s1, OP_SA);
		op_push(stat, s2, s1, OP_PA);
		if (case_id == 5)
			op_swap(stat, s1, OP_SA);
	}
}

void	three_sort_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2)
{
	int	top;
	int	mid;
	int	bot;

	if (get_stack_size(s1) < 3)
		return ;
	top = s1->datas[s1->top_index];
	mid = s1->datas[prev_idx(s1, s1->top_index)];
	bot = s1->datas[prev_idx(s1, prev_idx(s1, s1->top_index))];
	if (top < mid && mid < bot)
		return ;
	if (top < bot && bot < mid)
		three_sort_asc_cases(stat, s1, s2, 1);
	else if (mid < top && top < bot)
		three_sort_asc_cases(stat, s1, s2, 2);
	else if (bot < top && top < mid)
		three_sort_asc_cases(stat, s1, s2, 3);
	else if (mid < bot && bot < top)
		three_sort_asc_cases(stat, s1, s2, 4);
	else if (bot < mid && mid < top)
		three_sort_asc_cases(stat, s1, s2, 5);
}

void	three_sort_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2)
{
	int	i;

	if (get_stack_size(s2) < 3)
		return ;
	i = 0;
	while (i < 3)
	{
		if (get_stack_size(s2) >= 2 && s2->datas[s2->top_index]
			< s2->datas[prev_idx(s2, s2->top_index)])
			op_swap(stat, s2, OP_SB);
		op_push(stat, s2, s1, OP_PA);
		i++;
	}
	three_sort_asc(stat, s1, s2);
}
