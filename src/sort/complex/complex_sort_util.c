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
#include "merge_sort.h"
#include <stdlib.h>

void	find_pivot(t_stack *s, int size, int *pivot1, int *pivot2);
void	partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt);
void	partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt);
void	rewind_stack(t_stack *s1, t_stack *s2, int s1_size, int s2_size);

void	find_pivot(t_stack *s, int size, int *pivot1, int *pivot2)
{
	int	*arr;
	int	i;
	int	idx;

	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		return ;
	i = 0;
	idx = s->top_index;
	while (i < size)
	{
		arr[i] = s->datas[idx];
		idx = prev_idx(s, idx);
		i++;
	}
	merge_sort(arr, size);
	*pivot1 = arr[size / 3];
	*pivot2 = arr[(size * 2) / 3];
	free(arr);
}

void	partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt)
{
	int	pivot1;
	int	pivot2;

	cnt[0] = 0;
	cnt[1] = 0;
	cnt[2] = 0;
	find_pivot(s1, size, &pivot1, &pivot2);
	while (size--)
	{
		if (s1->datas[s1->top_index] >= pivot2)
			(rotate_stack(s1), cnt[0]++);
		else
		{
			push_stack(s1, s2);
			cnt[2]++;
			if (s2->datas[s2->top_index] >= pivot1)
				(rotate_stack(s2), cnt[1]++);
		}
	}
}

void	partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt)
{
	int	pivot1;
	int	pivot2;

	cnt[0] = 0;
	cnt[1] = 0;
	cnt[2] = 0;
	find_pivot(s2, size, &pivot1, &pivot2);
	while (size--)
	{
		if (s2->datas[s2->top_index] < pivot1)
			(rotate_stack(s2), cnt[2]++);
		else
		{
			push_stack(s2, s1);
			cnt[0]++;
			if (s1->datas[s1->top_index] < pivot2)
				(rotate_stack(s1), cnt[1]++);
		}
	}
}

void	rewind_stack(t_stack *s1, t_stack *s2, int s1_size, int s2_size)
{
	if (get_stack_size(s1) == s1_size && get_stack_size(s2) == s2_size)
		return ;
	if (get_stack_size(s1) == s1_size)
		while (s2_size--)
			rrotate_stack(s2);
	else if (get_stack_size(s2) == s2_size)
		while (s1_size--)
			rrotate_stack(s1);
	else
	{
		while (s1_size && s2_size)
		{
			rrotate_stacks(s1, s2);
			s1_size--;
			s2_size--;
		}
		while (s1_size--)
			rrotate_stack(s1);
		while (s2_size--)
			rrotate_stack(s2);
	}
}
