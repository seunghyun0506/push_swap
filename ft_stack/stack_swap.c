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

int			swap_stack(t_stack *s, t_op *op);
int			swap_stacks(t_stack *s1, t_stack *s2, t_op *op);
static void	swap(int *num1, int *num2);

int	swap_stack(t_stack *s, t_op *op)
{
	if (get_stack_size(s) <= 1)
	{
		if (op)
			*op = OP_NONE;
		return (0);
	}
	swap(&s->datas[s->top_index], &s->datas[prev_idx(s, s->top_index)]);
	return (1);
}

int	swap_stacks(t_stack *s1, t_stack *s2, t_op *op)
{
	if (get_stack_size(s1) <= 1 || get_stack_size(s2) <= 1)
	{
		if (op)
			*op = OP_NONE;
		return (0);
	}
	swap_stack(s1, 0);
	swap_stack(s2, 0);
	return (1);
}

static void	swap(int *num1, int *num2)
{
	int	tmp;

	tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}
