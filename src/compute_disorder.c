/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:35:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"
#include "push_swap.h"

double	compute_disorder(t_stack *a)
{
	int		size;
	int		mistakes;
	t_pair	idx;
	t_pair	cur;

	size = get_stack_size(a);
	if (size < 2)
		return (0.0);
	mistakes = 0;
	cur.i = a->top_index;
	idx.i = -1;
	while (++idx.i < size - 1)
	{
		cur.j = prev_idx(a, cur.i);
		idx.j = idx.i;
		while (++idx.j < size)
		{
			if (a->datas[cur.i] > a->datas[cur.j])
				mistakes++;
			cur.j = prev_idx(a, cur.j);
		}
		cur.i = prev_idx(a, cur.i);
	}
	return ((double)mistakes / ((double)size * (size - 1) / 2.0));
}
