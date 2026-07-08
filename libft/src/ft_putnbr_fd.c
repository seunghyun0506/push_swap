/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:13:06 by slim              #+#    #+#             */
/*   Updated: 2026/04/08 14:05:32 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char			buffer[10];
	int				pos;
	long long int	number;

	number = n;
	pos = 9;
	if (number < 0)
	{
		number *= -1L;
		write(fd, "-", 1);
	}
	buffer[pos--] = number % 10 + '0';
	number /= 10;
	while (number)
	{
		buffer[pos--] = number % 10 + '0';
		number /= 10;
	}
	write(fd, buffer + pos + 1, 10 - (pos + 1));
}
