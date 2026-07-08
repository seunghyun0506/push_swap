/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:10:05 by slim              #+#    #+#             */
/*   Updated: 2026/07/09 00:10:05 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtoi(const char *nptr, const char **pos)
{
	int	res;
	int	sign;

	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	else
		sign = 1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			break ;
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	*pos = nptr;
	return (res * sign);
}
