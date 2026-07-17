/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:53:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/17 23:53:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double a)
{
	double	low;
	double	high;
	double	mid;
	double	diff;

	if (a < 0)
		return (0.0);
	if (a == 0.0 || a == 1.0)
		return (a);
	low = 0.0;
	high = a;
	if (a < 1.0)
		high = 1.0;
	while (1)
	{
		mid = low + (high - low) / 2.0;
		diff = mid * mid - a;
		if (diff < 0)
			diff = -diff;
		if (diff < 0.00001)
			break ;
		if (mid * mid > a)
			high = mid;
		else
			low = mid;
	}
	return (mid);
}
