/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_basic_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:48:03 by slim              #+#    #+#             */
/*   Updated: 2026/05/12 21:48:03 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack_bonus.h"
#include "ft_stack_internal_bonus.h"
#include <stdlib.h>

t_stack	*init_stack(int capacity);
void	destroy_stack(t_stack *s);
int		push_stack_data(t_stack *s, int data);
int		pop_stack_data(t_stack *s, int *res);

t_stack	*init_stack(int capacity)
{
	t_stack	*res;

	res = (t_stack *)malloc(sizeof(t_stack));
	if (res == NULL)
		return (NULL);
	res->datas = (int *)malloc((capacity + 1) * sizeof(int));
	if (!res->datas)
	{
		free(res);
		return (NULL);
	}
	res->top_index = 0;
	res->bottom_index = 0;
	res->capacity = capacity;
	return (res);
}

int	push_stack_data(t_stack *s, int data)
{
	if (is_stack_full(s))
		return (~data);
	s->top_index = next_idx(s, s->top_index);
	s->datas[s->top_index] = data;
	return (data);
}

int	pop_stack_data(t_stack *s, int *res)
{
	if (get_stack_size(s) <= 0)
		return (0);
	*res = s->datas[s->top_index];
	s->top_index = prev_idx(s, s->top_index);
	return (1);
}

void	destroy_stack(t_stack *s)
{
	free(s->datas);
	free(s);
}
