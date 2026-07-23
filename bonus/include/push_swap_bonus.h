/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 11:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 11:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include "push_swap_stat_bonus.h"

int		str_to_int(const char *str, const char **pos, int *err);
int		parse_flag(t_push_swap_stat *stat);
int		parse_stack(t_push_swap_stat *stat);
int		check_duplicate(t_push_swap_stat *stat);
double	compute_disorder(t_stack *a);
void	print_bench_info(t_push_swap_stat *stat);
int		merge_sort(int *arr, int size);

#endif
