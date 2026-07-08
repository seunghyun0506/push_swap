/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:28:16 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 14:08:37 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*tmp;
	size_t				index;

	tmp = (const unsigned char *) s;
	index = 0;
	while (index < n)
	{
		if (tmp[index] == (unsigned char)c)
			return ((void *)(tmp + index));
		index++;
	}
	return ((void *)(0));
}
