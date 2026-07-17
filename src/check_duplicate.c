/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:52:07 by slim              #+#    #+#             */
/*   Updated: 2026/07/10 01:57:54 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap.h"
#include "push_swap_stat.h"

int	check_duplicate(t_push_swap_stat *stat);

int	check_duplicate(t_push_swap_stat *stat)
{
	int	size;
	int	i;

	size = get_stack_size(stat->stack_a);
	if (size <= 1)
		return (1);
	i = 0;
	while (i < size - 1)
	{
		if (stat->sorted[i] == stat->sorted[i + 1])
			return (0);
		i++;
	}
	return (1);
}
