/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicate_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 19:15:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack_bonus.h"
#include "ft_stack_internal_bonus.h"
#include "push_swap_bonus.h"

static int	has_dup(t_stack *s, int cur1, int i, int size);

int	check_duplicate(t_push_swap_stat *stat)
{
	int	size;
	int	i;
	int	cur;

	size = get_stack_size(stat->stack_a);
	if (size <= 1)
		return (1);
	cur = stat->stack_a->top_index;
	i = 0;
	while (i < size - 1)
	{
		if (has_dup(stat->stack_a, cur, i, size))
			return (0);
		cur = prev_idx(stat->stack_a, cur);
		i++;
	}
	return (1);
}

static int	has_dup(t_stack *s, int cur1, int i, int size)
{
	int	cur2;
	int	j;

	cur2 = prev_idx(s, cur1);
	j = i + 1;
	while (j < size)
	{
		if (s->datas[cur1] == s->datas[cur2])
			return (1);
		cur2 = prev_idx(s, cur2);
		j++;
	}
	return (0);
}
