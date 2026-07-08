/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:47:48 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 08:16:56 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	is_set(char c, char const *set)
{
	int	size;

	size = 0;
	while (set[size] != '\0')
	{
		if (c == set[size])
			return (1);
		size++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (start < end && is_set(s1[end - 1], set))
		end--;
	res = (char *)malloc((end - start + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[end - start] = '\0';
	return (ft_memcpy(res, s1 + start, end - start));
}
