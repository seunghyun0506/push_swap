/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:35:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 08:35:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap.h"

double	compute_disorder(t_stack *a)
{
	int	size;
	int	mistakes;
	int	total_pairs;
	int	i;
	int	j;

	size = get_stack_size(a);
	if (size < 2)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	i = size;
	while (i > 1)
	{
		j = i - 1;
		while (j >= 1)
		{
			total_pairs++;
			if (a->datas[i] > a->datas[j])
				mistakes++;
			j--;
		}
		i--;
	}
	return ((double)mistakes / (double)total_pairs);
}
