/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 02:02:08 by slim              #+#    #+#             */
/*   Updated: 2026/07/22 12:19:45 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap_stat.h"
#include "push_swap.h"
#include "merge_sort.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	free_resources(t_push_swap_stat *stat);
void		print_op_buffer(t_op_buffer *buffer);

int	main(int argc, char **argv)
{
	t_push_swap_stat	stat;

	if (argc <= 1)
		return (0);
	init_push_swap_stat(&stat, argc, argv);
	if (!stat.op_buffer || !parse_flag(&stat))
		return (free_resources(&stat), write(2, "Error\n", 6), 1);
	if (stat.i >= stat.argc)
		return (free_resources(&stat), 0);
	if (!parse_stack(&stat)
		|| !merge_sort(stat.sorted, get_stack_size(stat.stack_a)))
		return (free_resources(&stat), write(2, "Error\n", 6), 1);
	if (!check_duplicate(&stat))
		return (free_resources(&stat), write(2, "Error\n", 6), 1);
	sort(&stat);
	print_op_buffer(stat.op_buffer);
	if (stat.bench)
		print_bench_info(&stat);
	return (free_resources(&stat), 0);
}

void	print_op_buffer(t_op_buffer *buffer)
{
	int			i;
	const char	*names[13];

	if (!buffer || !buffer->arr)
		return ;
	names[OP_NONE] = "";
	names[OP_SA] = "sa\n";
	names[OP_SB] = "sb\n";
	names[OP_SS] = "ss\n";
	names[OP_PA] = "pa\n";
	names[OP_PB] = "pb\n";
	names[OP_RA] = "ra\n";
	names[OP_RB] = "rb\n";
	names[OP_RR] = "rr\n";
	names[OP_RRA] = "rra\n";
	names[OP_RRB] = "rrb\n";
	names[OP_RRR] = "rrr\n";
	i = 0;
	while (i < buffer->idx)
	{
		if (buffer->arr[i] >= OP_SA && buffer->arr[i] <= OP_RRR)
			ft_putstr_fd((char *)names[buffer->arr[i]], 1);
		i++;
	}
}

static void	free_resources(t_push_swap_stat *stat)
{
	if (!stat)
		return ;
	free_op_buffer(stat->op_buffer);
	stat->op_buffer = NULL;
	if (stat->stack_a)
		destroy_stack(stat->stack_a);
	stat->stack_a = NULL;
	if (stat->stack_b)
		destroy_stack(stat->stack_b);
	stat->stack_b = NULL;
	free(stat->sorted);
	stat->sorted = NULL;
}
