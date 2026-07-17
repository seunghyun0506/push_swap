/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecremove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:36:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 23:36:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	vecremove(t_vector *v, int idx)
{
	int	i;

	if (!v || idx < 0 || idx >= v->idx)
		return ;
	i = idx;
	while (i < v->idx - 1)
	{
		v->arr[i] = v->arr[i + 1];
		i++;
	}
	v->idx--;
}
