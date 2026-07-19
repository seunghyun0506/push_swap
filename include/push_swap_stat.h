/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stat.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 02:18:12 by slim              #+#    #+#             */
/*   Updated: 2026/07/08 02:18:12 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_STAT_H
# define PUSH_SWAP_STAT_H

# include "ft_stack.h"
# include "op_buffer.h"

typedef struct s_push_swap_stat
{
	int			argc;
	int			i;
	int			option;
	int			bench;
	char		**argv;
	t_stack		*stack_a;
	t_stack		*stack_b;
	int			*sorted;
	t_op_buffer	*op_buffer;
}	t_push_swap_stat;

void	init_push_swap_stat(t_push_swap_stat *stat, int argc, char **argv);

#endif
