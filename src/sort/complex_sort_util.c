/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 06:32:51 by slim              #+#    #+#             */
/*   Updated: 2026/07/12 14:45:18 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	find_pivot(t_stack *s, int size, int *pivot1, int *pivot2);
void	partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt);
void	partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt);
void	rewind_stack(t_stack *s1, t_stack *s2, int s1_size, int s2_size);

void	find_pivot(t_stack *s, int size, int *pivot1, int *pivot2)
{
	int	arr[10];
	int	idx;
	int	j;
	int	tmp;

	idx = -1;
	while (++idx < 10)
	{
		tmp = (size / 10) * idx + ((size % 10) * idx) / 10;
		arr[idx] = s->datas[(s->top_index + tmp) % (s->capacity + 1)];
	}
	idx = 0;
	while (++idx < 10)
	{
		tmp = arr[idx];
		j = idx;
		while (--j >= 0 && arr[j] > tmp)
			arr[j + 1] = arr[j];
		arr[j + 1] = tmp;
	}
	*pivot1 = arr[3];
	*pivot2 = arr[6];
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
		if (s1->datas[s1->top_index] < pivot1)
			(push_stack(s1, s2), cnt[0]++);
		else if (s1->datas[s1->top_index] <= pivot2)
			(push_stack(s1, s2), rotate_stack(s2), cnt[1]++);
		else
			(rotate_stack(s1), ++cnt[2]);
	}
}

void	partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt)
{
	int	pivot1;
	int	pivot2;

	cnt[0] = 0;
	cnt[1] = 0;
	cnt[2] = 0;
	find_pivot(s1, size, &pivot1, &pivot2);
	while (size--)
	{
		if (s1->datas[s1->top_index] < pivot1)
			(push_stack(s1, s2), rotate_stack(s2), cnt[1]++);
		else if (s1->datas[s1->top_index] <= pivot2)
			(push_stack(s1, s2), cnt[0]++);
		else
			(rotate_stack(s1), ++cnt[2]);
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