/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 06:55:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 19:15:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include "push_swap_bonus.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static int	execute_instruction(t_push_swap_stat *stat, char *line);
static int	run_instructions(t_push_swap_stat *stat);

int	main(int argc, char **argv)
{
	t_push_swap_stat	stat;

	if (argc <= 1)
		return (0);
	init_push_swap_stat(&stat, argc, argv);
	if (!parse_stack(&stat))
		return (free_resources(&stat), write(2, "Error\n", 6), 1);
	if (!check_duplicate(&stat))
		return (free_resources(&stat), write(2, "Error\n", 6), 1);
	if (!run_instructions(&stat))
		return (free_resources(&stat), write(2, "Error\n", 6), 1);
	if (is_sorted(stat.stack_a) && get_stack_size(stat.stack_b) == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (free_resources(&stat), 0);
}

static int	run_instructions(t_push_swap_stat *stat)
{
	char	*line;
	int		res;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		res = execute_instruction(stat, line);
		free(line);
		if (!res)
			return (0);
	}
	return (1);
}

static int	execute_instruction(t_push_swap_stat *stat, char *line)
{
	if (ft_strcmp(line, "sa\n") == 0)
		return (swap_stack(stat->stack_a, 0) || 1);
	if (ft_strcmp(line, "sb\n") == 0)
		return (swap_stack(stat->stack_b, 0) || 1);
	if (ft_strcmp(line, "ss\n") == 0)
		return (swap_stacks(stat->stack_a, stat->stack_b, 0) || 1);
	if (ft_strcmp(line, "pa\n") == 0)
		return (push_stack(stat->stack_b, stat->stack_a, 0) || 1);
	if (ft_strcmp(line, "pb\n") == 0)
		return (push_stack(stat->stack_a, stat->stack_b, 0) || 1);
	if (ft_strcmp(line, "ra\n") == 0)
		return (rotate_stack(stat->stack_a, 0) || 1);
	if (ft_strcmp(line, "rb\n") == 0)
		return (rotate_stack(stat->stack_b, 0) || 1);
	if (ft_strcmp(line, "rr\n") == 0)
		return (rotate_stacks(stat->stack_a, stat->stack_b, 0) || 1);
	if (ft_strcmp(line, "rra\n") == 0)
		return (rrotate_stack(stat->stack_a, 0) || 1);
	if (ft_strcmp(line, "rrb\n") == 0)
		return (rrotate_stack(stat->stack_b, 0) || 1);
	if (ft_strcmp(line, "rrr\n") == 0)
		return (rrotate_stacks(stat->stack_a, stat->stack_b, 0) || 1);
	return (0);
}
