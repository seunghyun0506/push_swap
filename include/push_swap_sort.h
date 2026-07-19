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

typedef struct s_divide
{
	int	chunk_size;
	int	total_chunks;
	int	mid;
	int	total_n;
	int	step;
	int	max_step;
	int	top_dist;
	int	bot_dist;
}	t_divide;

typedef struct s_lis
{
	int	*tails;
	int	*indices;
	int	*parent;
}	t_lis;

typedef struct s_part
{
	int	size;
	int	*cnt;
}	t_part;

int		complex_sort(t_push_swap_stat *stat);
int		medium_sort(t_push_swap_stat *stat);
void	divide_by_chunks(t_push_swap_stat *stat, int chunk_size,
			int total_chunks);
void	return_to_a_by_chunk(t_push_swap_stat *stat, int chunk_size,
			int total_chunks);
int		get_insert_pos_a(t_stack *a, int val);
void	calculate_move_cost(t_push_swap_stat *stat, int pos_a, int pos_b,
			t_cost *cost);
void	execute_move(t_push_swap_stat *stat, t_cost *cost);
void	align_stack_a(t_push_swap_stat *stat);
int		small_sort(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			int size);
int		small_sort_helper(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			int size);
void	three_sort_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2);
void	three_sort_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2);

int		get_rank(int *sorted, int n, int val);
int		calc_total_cost(t_cost *cost);

int		simple_sort(t_push_swap_stat *stat);
void	lis_to_b(t_push_swap_stat *stat);
void	greedy_to_a(t_push_swap_stat *stat);
void	align_a(t_push_swap_stat *stat);
void	map_lis_flags(t_push_swap_stat *stat, int *is_lis_datas);
int		find_best_non_lis_rot(t_push_swap_stat *stat, int *is_lis);

#endif
