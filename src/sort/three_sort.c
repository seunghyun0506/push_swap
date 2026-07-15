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
	int	arr[3];

	if (get_stack_size(s1) < 3)
		return ;
	arr[0] = s1->top_index;
	arr[1] = prev_idx(s1, arr[0]);
	arr[2] = prev_idx(s1, arr[1]);
	arr[0] = s1->datas[arr[0]];
	arr[1] = s1->datas[arr[1]];
	arr[2] = s1->datas[arr[2]];
	if (arr[0] < arr[1] && arr[1] < arr[2])
		return ;
	else if (arr[0] < arr[2] && arr[2] < arr[1])
		(rotate_stack(s1), swap_stack(s1), rrotate_stack(s1));
	else if (arr[1] < arr[0] && arr[0] < arr[2])
		swap_stack(s1);
	else if (arr[1] < arr[2] && arr[2] < arr[0])
		(push_stack(s1, s2), swap_stack(s1)
			, push_stack(s2, s1), swap_stack(s1));
	else if (arr[1] < arr[2] && arr[2] < arr[0])
		(swap_stack(s1), push_stack(s1, s2)
			, swap_stack(s1), push_stack(s2, s1));
	else if (arr[2] < arr[1] && arr[1] < arr[0])
		(swap_stack(s1), push_stack(s1, s2), swap_stack(s1)
			, push_stack(s2, s1), swap_stack(s1));
}

void	three_sort_desc(t_stack *s1, t_stack *s2)
{
	int	arr[3];

	if (get_stack_size(s1) < 3)
		return ;
	arr[0] = s1->top_index;
	arr[1] = prev_idx(s1, arr[0]);
	arr[2] = prev_idx(s1, arr[1]);
	arr[0] = s1->datas[arr[0]];
	arr[1] = s1->datas[arr[1]];
	arr[2] = s1->datas[arr[2]];
	if (arr[0] > arr[1] && arr[1] > arr[2])
		return ;
	else if (arr[0] > arr[2] && arr[2] > arr[1])
		(rotate_stack(s1), swap_stack(s1), rrotate_stack(s1));
	else if (arr[1] > arr[0] && arr[0] > arr[2])
		swap_stack(s1);
	else if (arr[2] > arr[0] && arr[0] > arr[1])
		(push_stack(s1, s2), swap_stack(s1)
			, push_stack(s2, s1), swap_stack(s1));
	else if (arr[1] > arr[2] && arr[2] > arr[0])
		(swap_stack(s1), push_stack(s1, s2)
			, swap_stack(s1), push_stack(s2, s1));
	else if (arr[2] > arr[1] && arr[1] > arr[0])
		(swap_stack(s1), push_stack(s1, s2), swap_stack(s1)
			, push_stack(s2, s1), swap_stack(s1));
}
