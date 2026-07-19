/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:38:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 20:54:02 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
#include "libft.h"
#include <stdlib.h>

void		map_lis_flags(t_push_swap_stat *stat, int *is_lis_datas);
int			find_best_non_lis_rot(t_push_swap_stat *stat, int *is_lis);
static int	binary_search_tails(int *tails, int len, int val);
static void	backtrace_lis(int *indices, int *parent, int len, int *is_lis);
static void	build_lis_flags(int *arr, int n, int *is_lis);

void	map_lis_flags(t_push_swap_stat *stat, int *is_lis_datas)
{
	int	*arr;
	int	*is_lis;
	int	cur_idx;
	int	i;

	arr = (int *)ft_calloc(get_stack_size(stat->stack_a) * 2, sizeof(int));
	if (!arr)
		return ;
	is_lis = arr + get_stack_size(stat->stack_a);
	cur_idx = stat->stack_a->top_index;
	i = -1;
	while (++i < get_stack_size(stat->stack_a))
	{
		arr[i] = stat->stack_a->datas[cur_idx];
		cur_idx = prev_idx(stat->stack_a, cur_idx);
	}
	build_lis_flags(arr, get_stack_size(stat->stack_a), is_lis);
	i = -1;
	while (++i < get_stack_size(stat->stack_a))
		is_lis_datas[get_rank(stat->sorted, stat->stack_a->capacity,
				arr[i])] = is_lis[i];
	free(arr);
}

int	find_best_non_lis_rot(t_push_swap_stat *stat, int *is_lis)
{
	int	i;
	int	min_rot;
	int	rot;
	int	cur_idx;

	min_rot = 0x7FFFFFFF;
	cur_idx = stat->stack_a->top_index;
	i = -1;
	while (++i < get_stack_size(stat->stack_a))
	{
		if (!is_lis[get_rank(stat->sorted, stat->stack_a->capacity,
					stat->stack_a->datas[cur_idx])])
		{
			rot = i;
			if (i > get_stack_size(stat->stack_a) / 2)
				rot = i - get_stack_size(stat->stack_a);
			if (abs(rot) < abs(min_rot))
				min_rot = rot;
		}
		cur_idx = prev_idx(stat->stack_a, cur_idx);
	}
	return (min_rot);
}

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

static void	backtrace_lis(int *indices, int *parent, int len, int *is_lis)
{
	int	curr;

	curr = indices[len - 1];
	while (curr != -1)
	{
		is_lis[curr] = 1;
		curr = parent[curr];
	}
}

static void	build_lis_flags(int *arr, int n, int *is_lis)
{
	t_lis	lis;
	int		len;
	int		i;
	int		idx;

	lis.tails = (int *)malloc(sizeof(int) * n * 3);
	if (!lis.tails)
		return ;
	lis.indices = lis.tails + n;
	lis.parent = lis.indices + n;
	len = 0;
	i = -1;
	while (++i < n)
	{
		lis.parent[i] = -1;
		idx = binary_search_tails(lis.tails, len, arr[i]);
		lis.tails[idx] = arr[i];
		lis.indices[idx] = i;
		if (idx > 0)
			lis.parent[i] = lis.indices[idx - 1];
		if (idx == len)
			len++;
	}
	backtrace_lis(lis.indices, lis.parent, len, is_lis);
	free(lis.tails);
}
