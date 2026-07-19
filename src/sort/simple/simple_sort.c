/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:44:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 12:44:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"

int	simple_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat->stack_a, stat->stack_b, n));
	lis_to_b(stat);
	greedy_to_a(stat);
	align_a(stat->stack_a);
	return (1);
}
