/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:57:02 by slim              #+#    #+#             */
/*   Updated: 2026/04/10 16:47:18 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_c;
	unsigned char		*dest_c;
	size_t				index;

	src_c = src;
	dest_c = dest;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		index = n - 1;
		while (index < (size_t)0 - 1)
		{
			dest_c[index] = src_c[index];
			index--;
		}
	}
	return (dest);
}
