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
	int	j;

	size = get_stack_size(stat->stack_a);
	i = 1;
	while (i <= size)
	{
		j = i + 1;
		while (j <= size)
		{
			if (stat->stack_a->datas[i] == stat->stack_a->datas[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
