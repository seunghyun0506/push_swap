/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort_utils.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 03:00:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 03:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_SORT_UTILS_H
# define PUSH_SWAP_SORT_UTILS_H

# include "ft_stack.h"
# include "push_swap_stat.h"

int		find_min_idx_stack(t_stack *s);
int		find_max_idx_stack(t_stack *s);
void	rotate_n(t_push_swap_stat *stat, t_stack *s, int rot);
int		binary_search(int *sorted, int n, int val);
int		get_insert_pos_a(t_stack *a, int val);

#endif
