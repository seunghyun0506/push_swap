/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:36:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 23:36:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include <stdlib.h>

static void	vec_resize(t_vector *v)
{
	int	*new_arr;
	int	i;

	v->capacity *= 2;
	new_arr = (int *)malloc(sizeof(int) * v->capacity);
	if (!new_arr)
		return ;
	i = 0;
	while (i < v->idx)
	{
		new_arr[i] = v->arr[i];
		i++;
	}
	free(v->arr);
	v->arr = new_arr;
}

void	vecadd_back(t_vector *v, int val)
{
	if (!v)
		return ;
	if (v->idx >= v->capacity)
		vec_resize(v);
	if (v->arr)
		v->arr[v->idx++] = val;
}
