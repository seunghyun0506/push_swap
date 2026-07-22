/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_sort.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 19:38:16 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 06:42:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_SORT_H
# define PUSH_SWAP_SORT_H
# include "ft_stack.h"
# include "push_swap_stat.h"

typedef struct s_pair
{
	int	i;
	int	j;
	int	cur_i;
	int	cur_j;
}	t_pair;

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
void	divide_by_chunks(t_push_swap_stat *stat);
void	return_to_a_by_chunk(t_push_swap_stat *stat);
int		get_insert_pos_a(t_stack *a, int val);
void	align_stack_a(t_push_swap_stat *stat);
int		small_sort(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			int size);
int		small_sort_helper(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
			int size);
void	three_sort_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2);
void	three_sort_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2);

int		get_rank(int *sorted, int n, int val);
int		get_num_chunks(int n);
int		is_in_chunk(t_push_swap_stat *stat, int rank, int chunk_idx);

int		simple_sort(t_push_swap_stat *stat);
void	align_a(t_push_swap_stat *stat);

#endif
