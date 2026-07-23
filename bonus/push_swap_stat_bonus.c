/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stat_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 19:30:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_stat_bonus.h"

void	init_push_swap_stat(t_push_swap_stat *stat, int argc, char **argv)
{
	stat->i = 1;
	stat->element_cnt = 0;
	stat->argc = argc;
	stat->argv = argv;
	stat->stack_a = 0;
	stat->stack_b = 0;
}
