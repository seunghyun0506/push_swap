/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:46:31 by slim              #+#    #+#             */
/*   Updated: 2026/07/16 15:24:14 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include <stdlib.h>

t_vector	*vecnew(int capacity)
{
	t_vector	*v;

	if (capacity < 1)
		capacity = 1;
	v = (t_vector *)malloc(sizeof(t_vector));
	if (!v)
		return (NULL);
	v->arr = (int *)malloc(sizeof(int) * capacity);
	if (!v->arr)
	{
		free(v);
		return (NULL);
	}
	v->idx = 0;
	v->capacity = capacity;
	return (v);
}