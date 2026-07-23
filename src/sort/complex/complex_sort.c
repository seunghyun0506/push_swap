/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 02:22:38 by slim              #+#    #+#             */
/*   Updated: 2026/07/16 13:53:20 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "ft_stack_internal.h"
#include "push_swap_sort.h"
#include "push_swap_stat.h"

int			complex_sort(t_push_swap_stat *stat);
static int	complex_sort_helper_a(t_push_swap_stat *stat, t_stack *s1,
				t_stack *s2, int size);
static int	complex_sort_helper_b(t_push_swap_stat *stat, t_stack *s1,
				t_stack *s2, int size);
void		find_pivot(t_push_swap_stat *stat, t_stack *s,
				int size, int *pivots);
void		partition_asc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_part *part);
void		partition_desc(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_part *part);
void		rewind_stack(t_push_swap_stat *stat, t_stack *s1, t_stack *s2,
				t_pair sizes);

int	complex_sort(t_push_swap_stat *stat)
{
	complex_sort_helper_a(stat, stat->stack_a, stat->stack_b,
		stat->element_cnt);
	return (1);
}

static int	complex_sort_helper_a(t_push_swap_stat *stat, t_stack *s1,
				t_stack *s2, int size)
{
	int		arr[3];
	t_part	part;
	t_pair	sizes;

	if (size <= 3)
		return (small_sort(stat, s1, s2, size));
	part.size = size;
	part.cnt = arr;
	partition_asc(stat, s1, s2, &part);
	sizes.i = arr[0];
	sizes.j = arr[1];
	rewind_stack(stat, s1, s2, sizes);
	complex_sort_helper_a(stat, s1, s2, arr[0]);
	complex_sort_helper_b(stat, s1, s2, arr[1]);
	complex_sort_helper_b(stat, s1, s2, arr[2] - arr[1]);
	return (1);
}

static int	complex_sort_helper_b(t_push_swap_stat *stat, t_stack *s1,
				t_stack *s2, int size)
{
	int		arr[3];
	t_part	part;
	t_pair	sizes;

	if (size <= 3)
		return (small_sort_helper(stat, s1, s2, size));
	part.size = size;
	part.cnt = arr;
	partition_desc(stat, s1, s2, &part);
	complex_sort_helper_a(stat, s1, s2, arr[0] - arr[1]);
	sizes.i = arr[1];
	sizes.j = arr[2];
	rewind_stack(stat, s1, s2, sizes);
	complex_sort_helper_a(stat, s1, s2, arr[1]);
	complex_sort_helper_b(stat, s1, s2, arr[2]);
	return (1);
}

void	find_pivot(t_push_swap_stat *stat, t_stack *s,
			int size, int *pivots)
{
	int	cur;
	int	i;
	int	min_val;
	int	max_val;
	int	ranks[2];

	if (size <= 0)
		return ;
	cur = s->top_index;
	min_val = s->datas[cur];
	max_val = min_val;
	i = -1;
	while (++i < size)
	{
		if (s->datas[cur] < min_val)
			min_val = s->datas[cur];
		if (s->datas[cur] > max_val)
			max_val = s->datas[cur];
		cur = prev_idx(s, cur);
	}
	ranks[0] = binary_search(stat->sorted, stat->element_cnt, min_val);
	ranks[1] = binary_search(stat->sorted, stat->element_cnt, max_val);
	pivots[0] = stat->sorted[ranks[0] + (ranks[1] - ranks[0]) / 3];
	pivots[1] = stat->sorted[ranks[0] + (ranks[1] - ranks[0]) * 2 / 3];
}
