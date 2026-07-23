/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort_utils.h"
#include "ft_stack_internal.h"

int	find_min_idx_stack(t_stack *s)
{
	int	cur;
	int	min_val;
	int	min_idx;
	int	size;
	int	i;

	size = get_stack_size(s);
	if (size == 0)
		return (-1);
	cur = s->top_index;
	min_val = s->datas[cur];
	min_idx = 0;
	i = 0;
	while (i < size)
	{
		if (s->datas[cur] < min_val)
		{
			min_val = s->datas[cur];
			min_idx = i;
		}
		cur = prev_idx(s, cur);
		i++;
	}
	return (min_idx);
}

int	find_max_idx_stack(t_stack *s)
{
	int	cur;
	int	max_val;
	int	max_idx;
	int	size;
	int	i;

	size = get_stack_size(s);
	if (size == 0)
		return (-1);
	cur = s->top_index;
	max_val = s->datas[cur];
	max_idx = 0;
	i = 0;
	while (i < size)
	{
		if (s->datas[cur] > max_val)
		{
			max_val = s->datas[cur];
			max_idx = i;
		}
		cur = prev_idx(s, cur);
		i++;
	}
	return (max_idx);
}

void	rotate_n(t_push_swap_stat *stat, t_stack *s, int rotation)
{
	if (!stat || !stat->op_buffer || stat->op_buffer->err)
		return ;
	while (rotation > 0 && !stat->op_buffer->err)
	{
		op_rotate(stat, s);
		rotation--;
	}
	while (rotation < 0 && !stat->op_buffer->err)
	{
		op_rrotate(stat, s);
		rotation++;
	}
}

int	binary_search(int *sorted, int n, int val)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (sorted[mid] == val)
			return (mid);
		if (sorted[mid] < val)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}
