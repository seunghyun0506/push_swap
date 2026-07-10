/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 02:22:38 by slim              #+#    #+#             */
/*   Updated: 2026/07/10 12:17:16 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap_stat.h"

int			complex_sort(t_push_swap_stat *stat);
static int	sort_asc(t_stack *s1, t_stack *s2, int size);
static int	sort_desc(t_stack *s1, t_stack *s2, int size);
void		find_pivot(t_stack *s, int size, int *pivot1, int *pivot2);
void		partition_asc(t_stack *s1, t_stack *s2, int size, int *cnt);
void		partition_desc(t_stack *s1, t_stack *s2, int size, int *cnt);
void		rewind_stack(t_stack *s1, t_stack *s2, int s1_size, int s2_size);

int	complex_sort(t_push_swap_stat *stat)
{
	sort_asc(stat->stack_a, stat->stack_b, get_stack_size(stat->stack_a));
	return (1);
}

static int	sort_asc(t_stack *s1, t_stack *s2, int size)
{
	int	arr[3];

	partition_asc(s1, s2, size, arr);
	rewind_stack(s1, s2, arr[2], arr[1]);
	sort_desc(s2, s1, arr[1]);
	sort_asc(s1, s2, arr[2]);
	while (arr[1]--)
		push_stack(s2, s1);
	sort_desc(s2, s1, arr[0]);
	while (arr[0]--)
		push_stack(s2, s1);
	return (1);
}

static int	sort_desc(t_stack *s1, t_stack *s2, int size)
{
	int	arr[3];

	partition_desc(s1, s2, size, arr);
	rewind_stack(s1, s2, arr[2], arr[1]);
	sort_asc(s2, s1, arr[1]);
	sort_desc(s1, s2, arr[2]);
	while (arr[1]--)
		push_stack(s2, s1);
	sort_asc(s2, s1, arr[0]);
	while (arr[0]--)
		push_stack(s2, s1);
	return (1);
}
