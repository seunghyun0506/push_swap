/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 15:42:05 by slim              #+#    #+#             */
/*   Updated: 2026/04/10 17:55:59 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	size_t	src_size;

	src_size = ft_strlen(s);
	index = 0;
	while (index <= src_size)
	{
		if (s[src_size - index] == (char)c)
			return ((char *)(s + src_size - index));
		index++;
	}
	return (0);
}
