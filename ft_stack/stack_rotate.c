/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 20:47:17 by slim              #+#    #+#             */
/*   Updated: 2026/07/06 11:33:12 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"

int	rotate_stack(t_stack *s);
int	rotate_stacks(t_stack *s1, t_stack *s2);

int	rotate_stack(t_stack *s)
{
	if (get_stack_size(s) <= 1)
		return (0);
	s->datas[s->bottom_index] = s->datas[s->top_index];
	s->top_index = prev_idx(s, s->top_index);
	s->bottom_index = prev_idx(s, s->bottom_index);
	return (1);
}

int	rotate_stacks(t_stack *s1, t_stack *s2)
{
	if (get_stack_size(s1) <= 1 || get_stack_size(s2) <= 1)
		return (0);
	return (rotate_stack(s1), rotate_stack(s2));
}
