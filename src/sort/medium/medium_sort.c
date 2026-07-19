/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 23:59:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "libft.h"

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;
	int	chunk_size;
	int	total_chunks;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat, stat->stack_a, stat->stack_b, n));
	chunk_size = (int)ft_sqrt((double)n);
	if (chunk_size == 0)
		chunk_size = 1;
	total_chunks = (n + chunk_size - 1) / chunk_size;
	divide_by_chunks(stat, chunk_size, total_chunks);
	return_to_a_by_chunk(stat, chunk_size, total_chunks);
	return (1);
}

static void	rotate_n(t_push_swap_stat *stat, t_stack *s, int n, t_op op_type)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if (op_type == OP_RRA || op_type == OP_RRB)
		{
			if (rrotate_stack(s))
				store_op(stat->op_buffer, op_type);
		}
		else
		{
			if (rotate_stack(s))
				store_op(stat->op_buffer, op_type);
		}
		i++;
	}
}

static void	exec_rr_rrr(t_push_swap_stat *stat, t_cost *cost, int shared)
{
	int		i;

	i = 0;
	while (i++ < shared)
	{
		if (cost->type == 0)
		{
			if (rotate_stacks(stat->stack_a, stat->stack_b))
				store_op(stat->op_buffer, OP_RR);
		}
		else
		{
			if (rrotate_stacks(stat->stack_a, stat->stack_b))
				store_op(stat->op_buffer, OP_RRR);
		}
	}
	if (cost->type == 0)
		rotate_n(stat, stat->stack_a, cost->cost_a - shared, OP_RA);
	else
		rotate_n(stat, stat->stack_a, cost->cost_a - shared, OP_RRA);
	if (cost->type == 0)
		rotate_n(stat, stat->stack_b, cost->cost_b - shared, OP_RB);
	else
		rotate_n(stat, stat->stack_b, cost->cost_b - shared, OP_RRB);
}

static void	exec_mixed(t_push_swap_stat *stat, t_cost *cost)
{
	t_op	op;

	op = OP_RA;
	if (cost->type == 3)
		op = OP_RRA;
	rotate_n(stat, stat->stack_a, cost->cost_a, op);
	op = OP_RRB;
	if (cost->type == 3)
		op = OP_RB;
	rotate_n(stat, stat->stack_b, cost->cost_b, op);
}

void	execute_move(t_push_swap_stat *stat, t_cost *cost)
{
	int		shared;

	if (cost->type == 0 || cost->type == 1)
	{
		shared = cost->cost_a;
		if (cost->cost_b < cost->cost_a)
			shared = cost->cost_b;
		exec_rr_rrr(stat, cost, shared);
	}
	else
		exec_mixed(stat, cost);
	if (push_stack(stat->stack_b, stat->stack_a))
		store_op(stat->op_buffer, OP_PA);
}
