/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 12:20:34 by slim              #+#    #+#             */
/*   Updated: 2026/07/08 12:20:34 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_stat.h"
#include "libft.h"

void	init_push_swap_stat(t_push_swap_stat *stat, int argc, char **argv)
{
	stat->i = 1;
	stat->option = 0;
	stat->bench = 0;
	stat->argc = argc;
	stat->argv = argv;
	stat->stack_a = 0;
	stat->stack_b = 0;
	stat->sorted = 0;
	stat->initial_disorder = 0.0;
	stat->selected_strategy = 0;
	stat->op_buffer = init_op_buffer();
}

int	parse_flag(t_push_swap_stat *stat)
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
		stat->i++;
	}
	if (opt_cnt > 1 || bench_cnt > 1)
		return (0);
	return (1);
}
