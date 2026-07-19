/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 11:24:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 18:37:47 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

void	greedy_to_a(t_push_swap_stat *stat);
int		calc_total_cost(t_cost *cost);

void	greedy_to_a(t_push_swap_stat *stat)
{
	t_cost	cost;
	t_cost	best;
	int		cur;
	int		size;
	int		i;

	while (get_stack_size(stat->stack_b) > 0)
	{
		size = get_stack_size(stat->stack_b);
		cur = stat->stack_b->top_index;
		best.cost_a = 10000000;
		best.cost_b = 10000000;
		best.type = 0;
		i = -1;
		while (++i < size)
		{
			calculate_move_cost(stat, get_insert_pos_a(stat->stack_a,
					stat->stack_b->datas[cur]), i, &cost);
			if (calc_total_cost(&cost) < calc_total_cost(&best))
				best = cost;
			cur = prev_idx(stat->stack_b, cur);
		}
		execute_move(stat, &best);
	}
}

int	calc_total_cost(t_cost *cost)
{
	int	total;

	if (cost->type == 0 || cost->type == 1)
	{
		total = cost->cost_a;
		if (cost->cost_b > cost->cost_a)
			total = cost->cost_b;
	}
	else
		total = cost->cost_a + cost->cost_b;
	return (total);
}
