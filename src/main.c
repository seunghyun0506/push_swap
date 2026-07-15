/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 02:02:08 by slim              #+#    #+#             */
/*   Updated: 2026/07/08 02:02:08 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap_stat.h"
#include "push_swap.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_push_swap_stat	stat;

	if (argc <= 1)
		return (0);
	init_push_swap_stat(&stat, argc, argv);
	if (!parse_flag(&stat))
		return (write(1, "Error\n", 6), 1);
	if (!parse_stack(&stat))
		return (write(1, "Error\n", 6), 1);
	if (!check_duplicate(&stat))
	{
		destroy_stack(stat.stack_a);
		destroy_stack(stat.stack_b);
		return (write(1, "Error\n", 6), 1);
	}
	sort(&stat);
}
