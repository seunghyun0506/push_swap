/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_util_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 06:58:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 06:58:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_stat.h"
#include <stdlib.h>

void	free_resources(t_push_swap_stat *stat)
{
	free_op_buffer(stat->op_buffer);
	destroy_stack(stat->stack_a);
	destroy_stack(stat->stack_b);
	free(stat->sorted);
}

int	is_sorted(t_stack *s)
{
	int	cur;
	int	i;
	int	size;

	size = get_stack_size(s);
	if (size <= 1)
		return (1);
	cur = s->top_index;
	i = 0;
	while (i < size - 1)
	{
		if (s->datas[cur] > s->datas[prev_idx(s, cur)])
			return (0);
		cur = prev_idx(s, cur);
		i++;
	}
	return (1);
}
