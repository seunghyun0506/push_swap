/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:05:03 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 12:12:22 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	total;

	if (size != 0 && nmemb != 0 && nmemb > ((size_t) 0 - 1) / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	total = nmemb * size;
	res = malloc(total);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, total);
	return (res);
}
