/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:11:51 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 09:53:46 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	s_size;
	size_t	index;

	s_size = ft_strlen(s);
	res = (char *) malloc((s_size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	index = 0;
	while (s[index])
	{
		res[index] = s[index];
		index++;
	}
	res[index] = '\0';
	return (res);
}
