/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:41:12 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 14:10:21 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp;
	const unsigned char	*tmp2;

	tmp = (unsigned char *) dest;
	tmp2 = (const unsigned char *) src;
	while (n--)
	{
		*tmp++ = *tmp2++;
	}
	return (dest);
}
