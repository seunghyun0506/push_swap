/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 05:22:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/22 08:34:42 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <unistd.h>

static void	print_disorder(t_push_swap_stat *stat);
static void	print_strategy(t_push_swap_stat *stat);
static void	print_counts(t_push_swap_stat *stat, int *counts);
static void	print_padded_nbr(int n, int width);

void	print_bench_info(t_push_swap_stat *stat)
{
	int	counts[13];

	print_disorder(stat);
	print_strategy(stat);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(stat->op_buffer->idx, 2);
	ft_putstr_fd("\n", 2);
	print_counts(stat, counts);
	ft_putstr_fd("[bench] ra: ", 2);
	print_padded_nbr(counts[OP_RA], 3);
	ft_putstr_fd(" rb: ", 2);
	print_padded_nbr(counts[OP_RB], 3);
	ft_putstr_fd(" rr: ", 2);
	print_padded_nbr(counts[OP_RR], 2);
	ft_putstr_fd(" rra: ", 2);
	print_padded_nbr(counts[OP_RRA], 3);
	ft_putstr_fd(" rrb: ", 2);
	print_padded_nbr(counts[OP_RRB], 4);
	ft_putstr_fd(" rrr: ", 2);
	print_padded_nbr(counts[OP_RRR], 3);
	ft_putstr_fd("\n", 2);
}

static void	print_disorder(t_push_swap_stat *stat)
{
	double	val;
	int		ipart;
	int		fpart;

	val = stat->initial_disorder * 100.0;
	ipart = (int)val;
	fpart = (int)((val - ipart) * 100.0 + 0.5);
	if (fpart >= 100)
	{
		ipart += 1;
		fpart -= 100;
	}
	ft_putstr_fd("[bench] disorder:  ", 2);
	ft_putnbr_fd(ipart, 2);
	ft_putstr_fd(".", 2);
	if (fpart < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(fpart, 2);
	ft_putstr_fd("%\n", 2);
}

static void	print_strategy(t_push_swap_stat *stat)
{
	ft_putstr_fd("[bench] strategy:  ", 2);
	if (stat->option == 1)
		ft_putstr_fd("Simple / O(n2)\n", 2);
	else if (stat->option == 2)
		ft_putstr_fd("Medium / O(n\xe2\x88\x9an)\n", 2);
	else if (stat->option == 3)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else
	{
		ft_putstr_fd("Adaptive / ", 2);
		if (stat->selected_strategy == 1)
			ft_putstr_fd("O(n2)\n", 2);
		else if (stat->selected_strategy == 2)
			ft_putstr_fd("O(n\xe2\x88\x9an)\n", 2);
		else
			ft_putstr_fd("O(n log n)\n", 2);
	}
}

static void	print_counts(t_push_swap_stat *stat, int *counts)
{
	int	i;

	i = 0;
	while (i < 13)
		counts[i++] = 0;
	i = 0;
	while (i < stat->op_buffer->idx)
	{
		if (stat->op_buffer->arr[i] >= OP_SA
			&& stat->op_buffer->arr[i] <= OP_RRR)
			counts[stat->op_buffer->arr[i]]++;
		i++;
	}
	ft_putstr_fd("[bench] sa: ", 2);
	print_padded_nbr(counts[OP_SA], 3);
	ft_putstr_fd(" sb: ", 2);
	print_padded_nbr(counts[OP_SB], 3);
	ft_putstr_fd(" ss: ", 2);
	print_padded_nbr(counts[OP_SS], 2);
	ft_putstr_fd(" pa: ", 2);
	print_padded_nbr(counts[OP_PA], 4);
	ft_putstr_fd(" pb: ", 2);
	print_padded_nbr(counts[OP_PB], 4);
	ft_putstr_fd("\n", 2);
}

static void	print_padded_nbr(int n, int width)
{
	int		len;
	long	val;

	val = n;
	len = 0;
	if (val <= 0)
		len++;
	while (val != 0)
	{
		val /= 10;
		len++;
	}
	while (len++ < width)
		write(2, " ", 1);
	ft_putnbr_fd(n, 2);
}
