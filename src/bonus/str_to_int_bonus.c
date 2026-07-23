/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_int_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 11:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap_bonus.h"
#include <limits.h>

static unsigned int	get_sign(const char **cur);
static unsigned int	get_limit(unsigned int sign);
static unsigned int	parse_digits(const char **cur, unsigned int limit,
						int *err);

int	str_to_int(const char *str, const char **pos, int *err)
{
	unsigned int	value;
	unsigned int	sign;

	*pos = str;
	while (ft_isspace(**pos))
		(*pos)++;
	sign = get_sign(pos);
	value = parse_digits(pos, get_limit(sign), err);
	if (*err)
		return (0);
	if (sign == 0 && value == (unsigned int)INT_MAX + 1U)
		return (INT_MIN);
	if (sign == 0)
		return (-(int)value);
	return ((int)value);
}

static unsigned int	get_sign(const char **cur)
{
	unsigned int	sign;

	sign = 1;
	if (**cur == '-' || **cur == '+')
	{
		if (**cur == '-')
			sign = 0;
		(*cur)++;
	}
	return (sign);
}

static unsigned int	get_limit(unsigned int sign)
{
	if (sign == 0)
		return ((unsigned int)INT_MAX + 1U);
	return ((unsigned int)INT_MAX);
}

static unsigned int	parse_digits(const char **cur, unsigned int limit,
		int *err)
{
	unsigned int	value;
	unsigned int	digit;
	unsigned int	count;
	unsigned int	overflow;

	value = 0;
	count = 0;
	overflow = 0;
	while (ft_isdigit(**cur))
	{
		digit = (unsigned int)(**cur - '0');
		if (value > (limit - digit) / 10)
			overflow = 1;
		else if (!overflow)
			value = value * 10 + digit;
		count++;
		(*cur)++;
	}
	*err = (count == 0 || overflow);
	return (value);
}
