/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:10:18 by slim              #+#    #+#             */
/*   Updated: 2026/05/12 22:10:18 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack_bonus.h"

int	get_stack_top(t_stack *s, int *res);
int	get_stack_size(t_stack *s);
int	next_idx(t_stack *s, int num);
int	prev_idx(t_stack *s, int num);
int	is_stack_full(t_stack *s);

int	get_stack_top(t_stack *s, int *res)
{
	if (get_stack_size(s) <= 0)
		return (0);
	*res = s->datas[s->top_index];
	return (1);
}

int	is_stack_full(t_stack *s)
{
	return (get_stack_size(s) == s->capacity);
}

int	get_stack_size(t_stack *s)
{
	int	size;

	size = (s->top_index - s->bottom_index + s->capacity + 1)
		% (s->capacity + 1);
	return (size);
}

int	next_idx(t_stack *s, int num)
{
	return ((num + 1) % (s->capacity + 1));
}

int	prev_idx(t_stack *s, int num)
{
	return ((num - 1 + (s->capacity + 1)) % (s->capacity + 1));
}
