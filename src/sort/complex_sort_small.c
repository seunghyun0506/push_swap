/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_small.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 15:30:41 by slim              #+#    #+#             */
/*   Updated: 2026/07/13 19:45:14 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"
#include <bits/types/siginfo_t.h>

int	small_sort_asc(t_stack *s1, t_stack *s2, int size);
int	small_sort_desc(t_stack *s1, t_stack *s2, int size);

int	small_sort_asc(t_stack *s1, t_stack *s2, int size)
{
	if (size <= 1)
		return (1);
	if (size == 2 && s1->datas[s1->top_index]
			> s1->datas[prev_idx(s1, s1->top_index)])
		return (swap_stack(s1));
	if (size == 3)
		return (three_sort_asc(s1, s2), 1);
	return (0);
}

int	small_sort_desc(t_stack *s1, t_stack *s2, int size)
{
	if (size <= 1)
		return (1);
	if (size == 2 && s1->datas[s1->top_index]
			< s1->datas[prev_idx(s1, s1->top_index)])
		return (swap_stack(s1));
	if (size == 3)
		return (three_sort_desc(s1, s2), 1);
	return (0);
}
