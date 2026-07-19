/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_cost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 00:05:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/18 00:05:00 by slim             ###   ########.fr       */
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

static int	get_min_opt_idx(int pos_a, int pos_b, int len_a, int len_b)
{
	int	opt[4];
	int	min_idx;
	int	i;

	opt[0] = pos_a;
	if (pos_b > pos_a)
		opt[0] = pos_b;
	opt[1] = len_a - pos_a;
	if (len_b - pos_b > opt[1])
		opt[1] = len_b - pos_b;
	opt[2] = pos_a + len_b - pos_b;
	opt[3] = len_a - pos_a + pos_b;
	min_idx = 0;
	i = 0;
	while (++i < 4)
	{
		if (opt[i] < opt[min_idx])
			min_idx = i;
	}
	return (min_idx);
}

void	calculate_move_cost(t_push_swap_stat *stat, int pos_a, int pos_b,
			t_cost *cost)
{
	int	len_a;
	int	len_b;

	len_a = get_stack_size(stat->stack_a);
	len_b = get_stack_size(stat->stack_b);
	cost->type = get_min_opt_idx(pos_a, pos_b, len_a, len_b);
	if (cost->type == 0 || cost->type == 2)
		cost->cost_a = pos_a;
	else
		cost->cost_a = len_a - pos_a;
	if (cost->type == 0 || cost->type == 3)
		cost->cost_b = pos_b;
	else
		cost->cost_b = len_b - pos_b;
}
