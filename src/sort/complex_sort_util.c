/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 06:32:51 by slim              #+#    #+#             */
/*   Updated: 2026/07/16 14:28:51 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

void	find_pivot(t_stack *s, int size, int *pivot1, int *pivot2);
void	partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt);
void	partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt);

void	find_pivot(t_stack *s, int size, int *pivot1, int *pivot2)
{
	int	arr[4];
	int	idx;
	int	j;
	int	tmp;

	idx = -1;
	while (++idx < 4)
	{
		tmp = (size / 4) * idx + ((size % 4) * idx) / 4;
		arr[idx] = s->datas[(s->top_index - tmp + s->capacity + 1) % (s->capacity + 1)];
	}
	idx = 0;
	while (++idx < 4)
	{
		tmp = arr[idx];
		j = idx;
		while (--j >= 0 && arr[j] > tmp)
			arr[j + 1] = arr[j];
		arr[j + 1] = tmp;
	}
	*pivot1 = arr[1];
	*pivot2 = arr[2];
}

void	partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt)
{
	int	pivot1;
	int	pivot2;

	cnt[0] = 0; // s2 위
	cnt[1] = 0; // s2 아래
	cnt[2] = 0; //남은 값
	find_pivot(s1, size, &pivot1, &pivot2);
	while (size--)
	{
		if (s1->datas[s1->top_index] <= pivot1)
			(push_stack(s1, s2), cnt[0]++);
		else if (s1->datas[s1->top_index] < pivot2)
			(push_stack(s1, s2), rotate_stack(s2), cnt[1]++);
		else
			(rotate_stack(s1), ++cnt[2]);
	}
}

void	partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt)
{
	int	pivot1;
	int	pivot2;

	cnt[0] = 0; //s2 위 
	cnt[1] = 0; //s2 아래
	cnt[2] = 0; //남은 값
	find_pivot(s1, size, &pivot1, &pivot2);
	while (size--)
	{
		if (s1->datas[s1->top_index] >= pivot2)
			(push_stack(s1, s2), cnt[0]++);
		else if (s1->datas[s1->top_index] > pivot1)
			(push_stack(s1, s2), rotate_stack(s2), cnt[1]++);
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
