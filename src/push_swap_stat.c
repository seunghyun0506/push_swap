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

void	init_push_swap_stat(t_push_swap_stat *stat, int argc, char **argv);

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
}
