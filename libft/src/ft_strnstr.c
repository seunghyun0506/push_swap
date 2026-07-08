/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:02:00 by slim              #+#    #+#             */
/*   Updated: 2026/04/15 14:21:57 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*little_tmp;
	const char	*big_tmp;
	size_t		len_tmp;

	if (little[0] == '\0')
		return ((char *)(big));
	while (*big && len)
	{
		big_tmp = big;
		little_tmp = little;
		len_tmp = len;
		while (*big_tmp && *little_tmp && len_tmp--)
		{
			if (*big_tmp != *little_tmp)
				break ;
			big_tmp++;
			little_tmp++;
		}
		if (*little_tmp == '\0')
			return ((char *)(big));
		big++;
		len--;
	}
	return (0);
}
