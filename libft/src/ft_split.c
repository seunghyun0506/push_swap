/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 09:33:10 by slim              #+#    #+#             */
/*   Updated: 2026/04/11 11:59:47 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static const char	*wc(char const *s, char c, size_t *cnt, char ***res);
static size_t		my_strlen(char const *s, char c);
static char			*my_strndup(char const *s, size_t size);
static char			failure(char **target, size_t cnt);
char				**ft_split(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	cnt;
	size_t	len;
	size_t	index;

	if (s == NULL)
		return (NULL);
	s = wc(s, c, &cnt, &res);
	if (!res)
		return (NULL);
	index = 0;
	while (index < cnt)
	{
		len = my_strlen(s, c);
		if (len != 0)
		{
			res[index++] = my_strndup(s, len);
			if (failure(res, index))
				return (NULL);
			s = s + len;
		}
		s++;
	}
	return (res);
}

static const char	*wc(char const *s, char c, size_t *p_cnt, char ***res)
{
	size_t	index;
	size_t	cnt;

	while (*s && *s == c)
		s++;
	index = 0;
	cnt = 0;
	while (s[index])
	{
		if (s[index] == c && s[index - 1] != c)
			cnt++;
		index++;
	}
	if (index != 0 && s[index - 1] != c)
		cnt++;
	*p_cnt = cnt;
	*res = (char **)malloc((cnt + 1) * sizeof(char *));
	if (*res)
		(*res)[cnt] = NULL;
	return (s);
}

static size_t	my_strlen(char const *s, char c)
{
	size_t	res;

	res = 0;
	while (*s && *s != c)
	{
		res++;
		s++;
	}
	return (res);
}

static char	*my_strndup(char const *s, size_t size)
{
	char	*res;
	size_t	index;

	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	index = 0;
	while (index < size)
	{
		res[index] = s[index];
		index++;
	}
	res[index] = '\0';
	return (res);
}

static char	failure(char **target, size_t cnt)
{
	size_t	index;

	if (target[cnt - 1] != NULL)
		return (0);
	index = 0;
	while (index < cnt)
	{
		free(target[index++]);
	}
	free(target);
	return (1);
}
