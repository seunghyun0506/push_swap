/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 10:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_SORT_UTILS_H
# define PUSH_SWAP_SORT_UTILS_H

# include "ft_stack.h"
# include "push_swap_stat.h"

void	op_push(t_push_swap_stat *stat, t_stack *from, t_stack *to);
void	op_rotate(t_push_swap_stat *stat, t_stack *s);
void	op_rrotate(t_push_swap_stat *stat, t_stack *s);
void	op_swap(t_push_swap_stat *stat, t_stack *s);
void	op_rrotate_stacks(t_push_swap_stat *stat, t_stack *s1, t_stack *s2);

int		find_min_idx_stack(t_stack *s);
int		find_max_idx_stack(t_stack *s);
void	rotate_n(t_push_swap_stat *stat, t_stack *s, int rotation);
int		binary_search(int *sorted, int n, int val);
int		get_insert_pos_a(t_stack *a, int val);

#endif
