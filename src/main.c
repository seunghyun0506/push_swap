/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 02:02:08 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 14:56:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_stat.h"
#include "push_swap.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static void	free_resources(t_push_swap_stat *stat)
{
	free_op_buffer(stat->op_buffer);
	destroy_stack(stat->stack_a);
	destroy_stack(stat->stack_b);
	free(stat->sorted);
}

static int	is_sorted(t_stack *s)
{
	int	cur;
	int	i;
	int	size;

	size = get_stack_size(s);
	if (size <= 1)
		return (1);
	cur = s->top_index;
	i = 0;
	while (i < size - 1)
	{
		if (s->datas[cur] > s->datas[prev_idx(s, cur)])
			return (0);
		cur = prev_idx(s, cur);
		i++;
	}
	return (1);
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

int	main(int argc, char **argv)
{
	t_push_swap_stat	stat;

	if (argc <= 1)
		return (0);
	init_push_swap_stat(&stat, argc, argv);
	if (!parse_flag(&stat) || !parse_stack(&stat))
		return (write(1, "Error\n", 6), 1);
	if (!check_duplicate(&stat))
		return (free_resources(&stat), write(1, "Error\n", 6), 1);
	if (is_sorted(stat.stack_a))
		return (free_resources(&stat), 0);
	sort(&stat);
	if (!stat.bench)
		print_op_buffer(stat.op_buffer);
	return (free_resources(&stat), 0);
}
