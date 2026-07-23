/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_small.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 15:30:41 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"

static void	push_twice(t_push_swap_stat *stat, t_stack *s1, t_stack *s2);

int	small_sort(t_push_swap_stat *stat, t_stack *s1, t_stack *s2, int size)
{
	if (size <= 1)
		return (1);
	if (size == 2 && s1->datas[s1->top_index]
		> s1->datas[prev_idx(s1, s1->top_index)])
	{
		op_swap(stat, s1);
		return (1);
	}
	if (size == 3)
	{
		three_sort_asc(stat, s1, s2);
		return (1);
	}
	return (0);
}

int	small_sort_helper(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
		int size)
{
	if (size == 1)
	{
		op_push(stat, s2, s1);
		return (1);
	}
	if (size == 2)
	{
		if (s2->datas[s2->top_index]
			< s2->datas[prev_idx(s2, s2->top_index)])
			op_swap(stat, s2);
		push_twice(stat, s1, s2);
		return (1);
	}
	if (size == 3)
		return (three_sort_desc(stat, s1, s2), 1);
	return (0);
}

static void	push_twice(t_push_swap_stat *stat, t_stack *s1, t_stack *s2)
{
	op_push(stat, s2, s1);
	op_push(stat, s2, s1);
}
