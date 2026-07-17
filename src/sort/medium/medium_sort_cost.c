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

int	get_insert_pos_a(t_stack *a, int val)
{
	int	size = get_stack_size(a);
	int	min_val, max_val, min_idx = 0;
	int	cur_idx, i, prev_val, cur;

	if (size == 0)
		return (0);
	cur_idx = a->top_index;
	min_val = a->datas[cur_idx];
	max_val = min_val;
	for (i = 0; i < size; i++)
	{
		if (a->datas[cur_idx] < min_val)
		{
			min_val = a->datas[cur_idx];
			min_idx = i;
		}
		if (a->datas[cur_idx] > max_val)
			max_val = a->datas[cur_idx];
		cur_idx = prev_idx(a, cur_idx);
	}
	if (val < min_val || val > max_val)
		return (min_idx);
	cur_idx = a->top_index;
	for (i = 0; i < size - 1; i++)
		cur_idx = prev_idx(a, cur_idx);
	prev_val = a->datas[cur_idx];
	cur_idx = a->top_index;
	for (i = 0; i < size; i++)
	{
		cur = a->datas[cur_idx];
		if (prev_val < val && val < cur)
			return (i);
		prev_val = cur;
		cur_idx = prev_idx(a, cur_idx);
	}
	return (0);
}

void	calculate_move_cost(int pos_b, int len_b, int pos_a, int len_a, t_cost *cost)
{
	int	cost_ra = pos_a;
	int	cost_rra = len_a - pos_a;
	int	cost_rb = pos_b;
	int	cost_rrb = len_b - pos_b;
	int	opt_rr, opt_rrr, opt_ra_rrb, opt_rra_rb, min_cost;

	opt_rr = cost_ra > cost_rb ? cost_ra : cost_rb;
	opt_rrr = cost_rra > cost_rrb ? cost_rra : cost_rrb;
	opt_ra_rrb = cost_ra + cost_rrb;
	opt_rra_rb = cost_rra + cost_rb;
	min_cost = opt_rr;
	cost->type = 0;
	cost->cost_a = cost_ra;
	cost->cost_b = cost_rb;
	if (opt_rrr < min_cost)
	{
		min_cost = opt_rrr;
		cost->type = 1;
		cost->cost_a = cost_rra;
		cost->cost_b = cost_rrb;
	}
	if (opt_ra_rrb < min_cost)
	{
		min_cost = opt_ra_rrb;
		cost->type = 2;
		cost->cost_a = cost_ra;
		cost->cost_b = cost_rrb;
	}
	if (opt_rra_rb < min_cost)
	{
		min_cost = opt_rra_rb;
		cost->type = 3;
		cost->cost_a = cost_rra;
		cost->cost_b = cost_rb;
	}
}
