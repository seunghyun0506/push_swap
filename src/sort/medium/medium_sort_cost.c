/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_cost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 00:05:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:49:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static int	get_min_idx(t_stack *a, int size, int *min_val, int *max_val)
{
	int	cur_idx;
	int	min_idx;
	int	i;

	cur_idx = a->top_index;
	*min_val = a->datas[cur_idx];
	*max_val = *min_val;
	min_idx = 0;
	i = 0;
	while (i < size)
	{
		if (a->datas[cur_idx] < *min_val)
		{
			*min_val = a->datas[cur_idx];
			min_idx = i;
		}
		if (a->datas[cur_idx] > *max_val)
			*max_val = a->datas[cur_idx];
		cur_idx = prev_idx(a, cur_idx);
		i++;
	}
	return (min_idx);
}

static int	search_insert_pos(t_stack *a, int size, int val)
{
	int	cur_idx;
	int	prev_val;
	int	i;

	cur_idx = a->top_index;
	i = 0;
	while (i < size - 1)
	{
		cur_idx = prev_idx(a, cur_idx);
		i++;
	}
	prev_val = a->datas[cur_idx];
	cur_idx = a->top_index;
	i = 0;
	while (i < size)
	{
		if (prev_val < val && val < a->datas[cur_idx])
			return (i);
		prev_val = a->datas[cur_idx];
		cur_idx = prev_idx(a, cur_idx);
		i++;
	}
	return (0);
}

int	get_insert_pos_a(t_stack *a, int val)
{
	int	size;
	int	min_val;
	int	max_val;
	int	min_idx;

	size = get_stack_size(a);
	if (size == 0)
		return (0);
	min_idx = get_min_idx(a, size, &min_val, &max_val);
	if (val < min_val || val > max_val)
		return (min_idx);
	return (search_insert_pos(a, size, val));
}
