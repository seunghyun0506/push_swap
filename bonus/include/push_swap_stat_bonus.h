/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stat_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 11:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_STAT_BONUS_H
# define PUSH_SWAP_STAT_BONUS_H

# include "ft_stack_bonus.h"
# include "op_buffer_bonus.h"

typedef struct s_push_swap_stat
{
	int			argc;
	int			i;
	int			option;
	int			bench;
	int			element_cnt;
	char		**argv;
	t_stack		*stack_a;
	t_stack		*stack_b;
	int			*sorted;
	t_op_buffer	*op_buffer;
	double		initial_disorder;
	int			selected_strategy;
}	t_push_swap_stat;

void	init_push_swap_stat(t_push_swap_stat *stat, int argc, char **argv);

#endif
