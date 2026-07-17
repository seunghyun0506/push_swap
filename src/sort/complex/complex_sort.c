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
#include "push_swap_sort.h"
#include "push_swap_stat.h"

int			complex_sort(t_push_swap_stat *stat);
static int	complex_sort_helper_a(t_stack *s1, t_stack *s2, int size);
static int	complex_sort_helper_b(t_stack *s1, t_stack *s2, int size);
void		find_pivot(t_stack *s, int size, int *pivot1, int *pivot2);
void		partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt);
void		partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt);
void		rewind_stack(t_stack *s1, t_stack *s2, int s1_size, int s2_size);

int	complex_sort(t_push_swap_stat *stat)
{
	complex_sort_helper_a(stat->stack_a, stat->stack_b, get_stack_size(stat->stack_a));
	return (1);
}

static int	complex_sort_helper_a(t_stack *s1, t_stack *s2, int size)
{
	int	arr[3];

	if (size <= 3)
		return (small_sort(s1, s2, size));
	partition_asc(s1, s2, size, arr);
	rewind_stack(s1, s2, arr[0], arr[1]);
	complex_sort_helper_a(s1, s2, arr[0]);
	complex_sort_helper_b(s1, s2, arr[1]);
	complex_sort_helper_b(s1, s2, arr[2] - arr[1]);
	return (1);
}

static int	complex_sort_helper_b(t_stack *s1, t_stack *s2, int size)
{
	int	arr[3];

	if (size <= 3)
		return (small_sort_helper(s1, s2, size));
	partition_desc(s1, s2, size, arr);
	complex_sort_helper_a(s1, s2, arr[0] - arr[1]);
	rewind_stack(s1, s2, arr[1], arr[2]);
	complex_sort_helper_a(s1, s2, arr[1]);
	complex_sort_helper_b(s1, s2, arr[2]);
	return (1);
}
