/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 19:38:16 by slim              #+#    #+#             */
/*   Updated: 2026/07/13 19:45:52 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_SORT_H
# define PUSH_SWAP_SORT_H
# include "ft_stack.h"

int		small_sort_asc(t_stack *s1, t_stack *s2, int size);
int		small_sort_desc(t_stack *s1, t_stack *s2, int size);
void	three_sort_asc(t_stack *s1, t_stack *s2);
void	three_sort_desc(t_stack *s1, t_stack *s2);

#endif
