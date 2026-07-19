/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:38:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 12:38:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
#include "libft.h"
#include <stdlib.h>

static int	binary_search_tails(int *tails, int len, int val)
{
	int	left;
	int	right;
	int	mid;
	int	res;

	left = 0;
	right = len - 1;
	res = len;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (tails[mid] >= val)
		{
			res = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return (res);
}

static void	build_lis_flags(int *arr, int n, int *is_lis)
{
	int	*tails;
	int	*indices;
	int	*parent;
	int	len;
	int	i;
	int	idx;
	int	curr;

	tails = (int *)malloc(sizeof(int) * n);
	indices = (int *)malloc(sizeof(int) * n);
	parent = (int *)malloc(sizeof(int) * n);
	if (!tails || !indices || !parent)
	{
		free(tails);
		free(indices);
		free(parent);
		return ;
	}
	len = 0;
	i = -1;
	while (++i < n)
	{
		parent[i] = -1;
		idx = binary_search_tails(tails, len, arr[i]);
		tails[idx] = arr[i];
		indices[idx] = i;
		if (idx > 0)
			parent[i] = indices[idx - 1];
		if (idx == len)
			len++;
	}
	curr = indices[len - 1];
	while (curr != -1)
	{
		is_lis[curr] = 1;
		curr = parent[curr];
	}
	free(tails);
	free(indices);
	free(parent);
}

static int	*get_lis_flags(t_stack *a, int n)
{
	int	*arr;
	int	*is_lis;
	int	cur_idx;
	int	i;

	arr = (int *)malloc(sizeof(int) * n);
	is_lis = (int *)ft_calloc(n, sizeof(int));
	if (!arr || !is_lis)
	{
		free(arr);
		free(is_lis);
		return (NULL);
	}
	cur_idx = a->top_index;
	i = -1;
	while (++i < n)
	{
		arr[i] = a->datas[cur_idx];
		cur_idx = prev_idx(a, cur_idx);
	}
	build_lis_flags(arr, n, is_lis);
	free(arr);
	return (is_lis);
}

static int	find_best_non_lis_rot(t_stack *a, int *is_lis, int n)
{
	int	i;
	int	min_rot;
	int	rot;
	int	cur_idx;

	min_rot = 2147483647;
	cur_idx = a->top_index;
	i = -1;
	while (++i < n)
	{
		if (!is_lis[cur_idx])
		{
			if (i <= n / 2)
				rot = i;
			else
				rot = i - n;
			if (abs(rot) < abs(min_rot))
				min_rot = rot;
		}
		cur_idx = prev_idx(a, cur_idx);
	}
	return (min_rot);
}

static void	map_lis_flags(t_stack *a, int n, int *is_lis_datas)
{
	int	*flags;
	int	cur_idx;
	int	i;

	flags = get_lis_flags(a, n);
	if (!flags)
		return ;
	cur_idx = a->top_index;
	i = -1;
	while (++i < n)
	{
		is_lis_datas[cur_idx] = flags[i];
		cur_idx = prev_idx(a, cur_idx);
	}
	free(flags);
}

void	lis_to_b(t_push_swap_stat *stat)
{
	int	n;
	int	*is_lis_datas;
	int	min_rot;
	int	i;

	n = get_stack_size(stat->stack_a);
	if (n <= 1)
		return ;
	is_lis_datas = (int *)ft_calloc(stat->stack_a->capacity + 1, sizeof(int));
	if (!is_lis_datas)
		return ;
	map_lis_flags(stat->stack_a, n, is_lis_datas);
	while (1)
	{
		n = get_stack_size(stat->stack_a);
		min_rot = find_best_non_lis_rot(stat->stack_a, is_lis_datas, n);
		if (min_rot == 2147483647)
			break ;
		if (min_rot > 0)
		{
			i = -1;
			while (++i < min_rot)
				rotate_stack(stat->stack_a);
		}
		else
		{
			i = -1;
			while (++i < abs(min_rot))
				rrotate_stack(stat->stack_a);
		}
		push_stack(stat->stack_a, stat->stack_b);
	}
	free(is_lis_datas);
}
