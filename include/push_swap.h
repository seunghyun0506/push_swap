/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:51:42 by slim              #+#    #+#             */
/*   Updated: 2026/07/09 13:51:42 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "push_swap_stat.h"

int		parse_flag(t_push_swap_stat *stat);
int		parse_stack(t_push_swap_stat *stat);
void	sort(t_push_swap_stat *stat);
int		check_duplicate(t_push_swap_stat *stat);
double	compute_disorder(t_stack *a);

#endif
