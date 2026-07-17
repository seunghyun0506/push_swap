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

void	three_sort_asc(t_stack *s1, t_stack *s2);
void	three_sort_desc(t_stack *s1, t_stack *s2);

void	three_sort_asc(t_stack *s1, t_stack *s2)
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
	else if (top < bot && bot < mid)
		(push_stack(s1, s2), swap_stack(s1), push_stack(s2, s1));
	else if (mid < top && top < bot)
		swap_stack(s1);
	else if (bot < top && top < mid)
		(push_stack(s1, s2), swap_stack(s1)
			, push_stack(s2, s1), swap_stack(s1));
	else if (mid < bot && bot < top)
		(swap_stack(s1), push_stack(s1, s2)
			, swap_stack(s1), push_stack(s2, s1));
	else if (bot < mid && mid < top)
		(swap_stack(s1), push_stack(s1, s2), swap_stack(s1)
			, push_stack(s2, s1), swap_stack(s1));
}

void	three_sort_desc(t_stack *s1, t_stack *s2)
{
	int	i;

	if (get_stack_size(s2) < 3)
		return ;
	i = 0;
	while (i < 3)
	{
		if (get_stack_size(s2) >= 2 && s2->datas[s2->top_index]
				< s2->datas[prev_idx(s2, s2->top_index)])
			swap_stack(s2);
		push_stack(s2, s1);
		i++;
	}
	three_sort_asc(s1, s2);
}
