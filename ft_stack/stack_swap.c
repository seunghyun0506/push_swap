/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 18:32:53 by slim              #+#    #+#             */
/*   Updated: 2026/07/06 11:32:26 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"

int			swap_stack(t_stack *s);
int			swap_stacks(t_stack *s1, t_stack *s2);
static void	swap(int *num1, int *num2);

int	swap_stack(t_stack *s)
{
	if (get_stack_size(s) <= 1)
		return (0);
	swap(&s->datas[s->top_index], &s->datas[calculate_next_index(s, s->top_index)]);
	return (1);
}

int	swap_stacks(t_stack *s1, t_stack *s2)
{
	if (get_stack_size(s1) <= 1 || get_stack_size(s2) <= 1)
		return (0);
	return (swap_stack(s1), swap_stack(s2));
}

static void	swap(int *num1, int *num2)
{
	int	tmp;

	tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}
