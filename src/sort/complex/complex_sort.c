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
				int *sizes);

int	complex_sort(t_push_swap_stat *stat)
{
	complex_sort_helper_a(stat, stat->stack_a, stat->stack_b,
		get_stack_size(stat->stack_a));
	return (1);
}

static int	complex_sort_helper_a(t_push_swap_stat *stat, t_stack *s1,
				t_stack *s2, int size)
{
	int		arr[3];
	t_part	part;
	int		rewind_sizes[2];

	if (size <= 3)
		return (small_sort(stat, s1, s2, size));
	part.size = size;
	part.cnt = arr;
	partition_asc(stat, s1, s2, &part);
	rewind_sizes[0] = arr[0];
	rewind_sizes[1] = arr[1];
	rewind_stack(stat, s1, s2, rewind_sizes);
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
	int		rewind_sizes[2];

	if (size <= 3)
		return (small_sort_helper(stat, s1, s2, size));
	part.size = size;
	part.cnt = arr;
	partition_desc(stat, s1, s2, &part);
	complex_sort_helper_a(stat, s1, s2, arr[0] - arr[1]);
	rewind_sizes[0] = arr[1];
	rewind_sizes[1] = arr[2];
	rewind_stack(stat, s1, s2, rewind_sizes);
	complex_sort_helper_a(stat, s1, s2, arr[1]);
	complex_sort_helper_b(stat, s1, s2, arr[2]);
	return (1);
}

/*
** find_pivot
** : stat->sorted(파싱 시 1회만 정렬된 배열)를 활용하여
**   현재 부분 스택 s의 원소들 중 1/3, 2/3 순위에 해당하는 피벗 값을 구합니다.
**   기존에는 호출마다 malloc + merge_sort를 수행했지만,
**   이제는 get_rank(O(log n)) 조회만으로 피벗을 선택합니다.
**   pivots[0] = 1/3 피벗, pivots[1] = 2/3 피벗
*/
void	find_pivot(t_push_swap_stat *stat, t_stack *s,
			int size, int *pivots)
{
	int	n;
	int	range[2];
	int	cur;
	int	i;
	int	rank;

	n = get_stack_size(stat->stack_a) + get_stack_size(stat->stack_b);
	cur = s->top_index;
	range[0] = n;
	range[1] = -1;
	i = 0;
	while (i < size)
	{
		rank = get_rank(stat->sorted, n, s->datas[cur]);
		if (rank < range[0])
			range[0] = rank;
		if (rank > range[1])
			range[1] = rank;
		cur = prev_idx(s, cur);
		i++;
	}
	pivots[0] = stat->sorted[range[0] + (range[1] - range[0]) / 3];
	pivots[1] = stat->sorted[range[0] + (range[1] - range[0]) * 2 / 3];
}
