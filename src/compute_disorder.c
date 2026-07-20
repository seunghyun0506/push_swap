/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 08:35:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:45:00 by slim             ###   ########.fr       */
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
	t_pair	p;

	size = get_stack_size(a);
	if (size < 2)
		return (0.0);
	mistakes = 0;
	p.cur_i = a->top_index;
	p.i = 0;
	while (p.i < size - 1)
	{
		p.cur_j = prev_idx(a, p.cur_i);
		p.j = p.i + 1;
		while (p.j < size)
		{
			if (a->datas[p.cur_i] > a->datas[p.cur_j])
				mistakes++;
			p.cur_j = prev_idx(a, p.cur_j);
			p.j++;
		}
		p.cur_i = prev_idx(a, p.cur_i);
		p.i++;
	}
	return ((double)mistakes / ((double)size * (size - 1) / 2.0));
}
