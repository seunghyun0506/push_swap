/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 06:33:55 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "libft.h"

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat, stat->stack_a, stat->stack_b, n));
	divide_by_chunks(stat);
	return_to_a_by_chunk(stat);
	return (1);
}

int	get_rank(int *sorted, int n, int val)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = n - 1;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (sorted[mid] == val)
			return (mid);
		if (sorted[mid] < val)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}

int	get_num_chunks(int n)
{
	int	chunk_size;

	chunk_size = (int)ft_sqrt((double)n);
	if (chunk_size == 0)
		chunk_size = 1;
	return ((n + chunk_size - 1) / chunk_size);
}

int	is_in_chunk(t_push_swap_stat *stat, int rank, int chunk_idx)
{
	int	num_chunks;
	int	chunk_size;
	int	limit;
	int	n;

	n = get_stack_size(stat->stack_a) + get_stack_size(stat->stack_b);
	num_chunks = get_num_chunks(n);
	chunk_size = (n + num_chunks - 1) / num_chunks;
	if (n >= 6)
		limit = n - 3;
	else
		limit = n;
	if (chunk_idx == num_chunks - 1)
		return (rank >= chunk_idx * chunk_size && rank < limit);
	return (rank >= chunk_idx * chunk_size
		&& rank < (chunk_idx + 1) * chunk_size);
}
