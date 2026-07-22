/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 04:17:46 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:06:58 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"

int	push_stack(t_stack *from, t_stack *to, t_op *op)
{
	int	res;

	if (get_stack_size(from) == 0)
	{
		if (op)
			*op = OP_NONE;
		return (0);
	}
	if (!pop_stack_data(from, &res))
	{
		if (op)
			*op = OP_NONE;
		return (0);
	}
	push_stack_data(to, res);
	return (1);
}
