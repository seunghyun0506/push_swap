/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_cost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 00:05:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 07:48:42 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"

int			get_insert_pos_a(t_stack *a, int val);
static int	get_min_idx(t_stack *a, int size, int *min_val, int *max_val);
static int	search_insert_pos(t_stack *a, int size, int val);

/*
** get_insert_pos_a
** : 스택 B에서 가져온 값(val)이 스택 A 내부의 어느 위치(인덱스)에
**   들어가는 것이 오름차순 정렬 상태를 유지하는지 탐색하여 인덱스를 반환합니다.
**
**   1) 스택 A의 최솟값, 최댓값, 최솟값 위치(min_idx)를 탐색합니다.
**   2) val이 A의 최솟값보다 작거나 최댓값보다 크면 min_idx를 반환합니다.
**   3) val이 범위 내라면 search_insert_pos()를 호출하여 올바른 위치를 반환합니다.
*/
int	get_insert_pos_a(t_stack *a, int val)
{
	int	size;
	int	min_val;
	int	max_val;
	int	min_idx;

	size = get_stack_size(a);
	if (size == 0)
		return (0);
	min_idx = get_min_idx(a, size, &min_val, &max_val);
	if (val < min_val || val > max_val)
		return (min_idx);
	return (search_insert_pos(a, size, val));
}

/*
** get_min_idx
** : 스택 A 전체를 순회하면서 최솟값(*min_val), 최댓값(*max_val),
**   그리고 최솟값이 위치한 인덱스(min_idx)를 단 한번의 순회로 찾아냅니다.
*/
static int	get_min_idx(t_stack *a, int size, int *min_val, int *max_val)
{
	int	cur;
	int	min_idx;
	int	i;

	cur = a->top_index;
	*min_val = a->datas[cur];
	*max_val = *min_val;
	min_idx = 0;
	i = 0;
	while (i < size)
	{
		if (a->datas[cur] < *min_val)
		{
			*min_val = a->datas[cur];
			min_idx = i;
		}
		if (a->datas[cur] > *max_val)
			*max_val = a->datas[cur];
		cur = prev_idx(a, cur);
		i++;
	}
	return (min_idx);
}

/*
** search_insert_pos
** : val이 (min_val < val < max_val) 범위일 때 사용됩니다.
**   스택 A를 순회하며 prev_val < val < cur_val 관계를 만족하는
**   두 원소 사이의 삽입 위치 인덱스를 반환합니다.
**
**   1) 스택 A의 맨 바텀 원소를 prev_val의 초기값으로 지정합니다.
**   2) Top부터 바텀까지 순회하며 prev_val < val < datas[cur] 만족 지점을 찾습니다.
*/
static int	search_insert_pos(t_stack *a, int size, int val)
{
	int	cur;
	int	prev_val;
	int	i;

	cur = a->top_index;
	i = 0;
	while (i < size - 1)
	{
		cur = prev_idx(a, cur);
		i++;
	}
	prev_val = a->datas[cur];
	cur = a->top_index;
	i = 0;
	while (i < size)
	{
		if (prev_val < val && val < a->datas[cur])
			return (i);
		prev_val = a->datas[cur];
		cur = prev_idx(a, cur);
		i++;
	}
	return (0);
}
