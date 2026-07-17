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
# include "push_swap_stat.h"

typedef struct s_cost
{
	int	type;
	int	cost_a;
	int	cost_b;
}	t_cost;

int		complex_sort(t_push_swap_stat *stat);
int		medium_sort(t_push_swap_stat *stat);
void	divide_by_chunks(t_push_swap_stat *stat, int chunk_size, int total_chunks);
void	return_to_a_by_chunk(t_push_swap_stat *stat, int chunk_size, int total_chunks);
int		get_insert_pos_a(t_stack *a, int val);
void	calculate_move_cost(int pos_b, int len_b, int pos_a, int len_a, t_cost *cost);
void	execute_move(t_push_swap_stat *stat, t_cost *cost);
void	align_stack_a(t_stack *a);
int		small_sort(t_stack *s1, t_stack *s2, int size);
int		small_sort_helper(t_stack *s1, t_stack *s2, int size);
void	three_sort_asc(t_stack *s1, t_stack *s2);
void	three_sort_desc(t_stack *s1, t_stack *s2);

#endif
