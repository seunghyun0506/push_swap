/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:40:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 12:40:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

static int	calc_total_cost(t_cost *cost)
{
	if (cost->type == 0 || cost->type == 1)
	{
		if (cost->cost_a > cost->cost_b)
			return (cost->cost_a);
		return (cost->cost_b);
	}
	return (cost->cost_a + cost->cost_b);
}

void	greedy_to_a(t_push_swap_stat *stat)
{
	int		len_a;
	int		len_b;
	int		cur_b_idx;
	int		i;
	int		val;
	int		pos_a;
	int		total_cost;
	int		min_cost;
	t_cost	cur_cost;
	t_cost	best_cost;

	while (get_stack_size(stat->stack_b) > 0)
	{
		len_b = get_stack_size(stat->stack_b);
		len_a = get_stack_size(stat->stack_a);
		cur_b_idx = stat->stack_b->top_index;
		min_cost = 2147483647;
		i = -1;
		while (++i < len_b)
		{
			val = stat->stack_b->datas[cur_b_idx];
			pos_a = get_insert_pos_a(stat->stack_a, val);
			calculate_move_cost(i, len_b, pos_a, len_a, &cur_cost);
			total_cost = calc_total_cost(&cur_cost);
			if (total_cost < min_cost)
			{
				min_cost = total_cost;
				best_cost = cur_cost;
			}
			cur_b_idx = prev_idx(stat->stack_b, cur_b_idx);
		}
		execute_move(stat, &best_cost);
	}
}
