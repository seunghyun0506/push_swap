/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_rrotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 10:48:57 by slim              #+#    #+#             */
/*   Updated: 2026/07/04 11:45:15 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"

int	rrotate_stack(t_stack *s);
int	rrotate_stacks(t_stack *s1, t_stack *s2);

int	rrotate_stack(t_stack *s)
{
	if (get_stack_size(s) <= 1)
		return (0);
	s->top_index = calculate_prev_index(s, s->top_index);
	s->bottom_index = calculate_prev_index(s, s->bottom_index);
	s->datas[s->top_index] = s->datas[s->bottom_index];
	return (1);
}

int	rrotate_stacks(t_stack *s1, t_stack *s2)
{
	return (rrotate_stack(s1) | rrotate_stack(s2));
}
