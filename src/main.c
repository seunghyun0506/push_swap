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

#include "push_swap_stat.h"
#include <unistd.h>
#include "libft.h"

static int	parse_flag(t_push_swap_stat *stat);
static int	parse_stack(t_push_swap_stat *stat);
static void	sort(t_push_swap_stat *stat);

int	main(int argc, char **argv)
{
	t_push_swap_stat	stat;

	if (argc <= 1)
		return (write(1, "Error\n", 6), 1);
	init_push_swap_stat(&stat, argc, argv);
	if (!parse_flag(&stat))
		return (write(1, "Error\n", 6), 1);
	if (!parse_stack(&stat))
		return (write(1, "Error\n", 6), 1);
	sort(&stat);
}

static int	parse_flag(t_push_swap_stat *stat)
{
	int	opt_cnt;
	int	bench_cnt;

	opt_cnt = 0;
	bench_cnt = 0;
	while (stat->i < stat->argc)
	{
		if (ft_strcmp(stat->argv[stat->i], "--simple") == 0 && ++opt_cnt)
			stat->option = 1;
		else if (ft_strcmp(stat->argv[stat->i], "--medium") == 0 && ++opt_cnt)
			stat->option = 2;
		else if (ft_strcmp(stat->argv[stat->i], "--complex") == 0 && ++opt_cnt)
			stat->option = 3;
		else if (ft_strcmp(stat->argv[stat->i], "--adaptive") == 0 && ++opt_cnt)
			stat->option = 0;
		else if (ft_strcmp(stat->argv[stat->i], "--bench") == 0 && ++bench_cnt)
			stat->bench = 1;
		else
			break ;
	}
	if (opt_cnt > 1 || bench_cnt > 1)
		return (0);
	return (1);
}

static void	sort(t_push_swap_stat *stat)
{
	
}
