/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:27:13 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 12:04:06 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	operate(char *buffer, long long int *number, int *pos);

char	*ft_itoa(int n)
{
	char			buffer[11];
	char			*res;
	int				pos;
	long long int	number;

	number = n;
	pos = 10;
	buffer[0] = 0;
	if (number < 0)
		number *= -1L;
	if (n < 0)
		buffer[0] = 1;
	operate(buffer, &number, &pos);
	while (number)
		operate(buffer, &number, &pos);
	res = (char *)malloc(sizeof(char) * (11 - (pos + 1) + buffer[0] + 1));
	if (!res)
		return (NULL);
	if (buffer[0])
		res[0] = '-';
	ft_memcpy(res + buffer[0], buffer + pos + 1, (11 - (pos + 1)));
	res[11 - (pos + 1) + buffer[0]] = '\0';
	return (res);
}

void	operate(char *buffer, long long int *number, int *pos)
{
	buffer[(*pos)--] = *number % 10 + '0';
	*number /= 10;
}
