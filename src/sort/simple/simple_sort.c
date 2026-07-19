/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:44:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 20:55:16 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "libft.h"
#include <stdlib.h>

int			simple_sort(t_push_swap_stat *stat);
void		lis_to_b(t_push_swap_stat *stat);
static void	rotate_a_n(t_push_swap_stat *stat, int min_rot);

int	simple_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat, stat->stack_a, stat->stack_b, n));
	lis_to_b(stat);
	greedy_to_a(stat);
	align_a(stat);
	return (1);
}

void	lis_to_b(t_push_swap_stat *stat)
{
	int		*is_lis_datas;
	int		min_rot;

	if (get_stack_size(stat->stack_a) <= 1)
		return ;
	is_lis_datas = (int *)ft_calloc(stat->stack_a->capacity + 1, sizeof(int));
	if (!is_lis_datas)
		return ;
	map_lis_flags(stat, is_lis_datas);
	while (1)
	{
		min_rot = find_best_non_lis_rot(stat, is_lis_datas);
		if (min_rot == 0x7FFFFFFF)
			break ;
		rotate_a_n(stat, min_rot);
		if (push_stack(stat->stack_a, stat->stack_b))
			store_op(stat->op_buffer, OP_PB);
	}
	free(is_lis_datas);
}

static void	rotate_a_n(t_push_swap_stat *stat, int min_rot)
{
	int		i;

	i = -1;
	if (min_rot > 0)
	{
		while (++i < min_rot)
		{
			if (rotate_stack(stat->stack_a))
				store_op(stat->op_buffer, OP_RA);
		}
	}
	else
	{
		while (++i < abs(min_rot))
		{
			if (rrotate_stack(stat->stack_a))
				store_op(stat->op_buffer, OP_RRA);
		}
	}
}
