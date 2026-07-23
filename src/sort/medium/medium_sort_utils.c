/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 12:30:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 05:30:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_stat.h"
#include "push_swap_sort_utils.h"
#include "libft.h"

int	get_num_chunks(int n)
{
	int	chunk_size;

	chunk_size = (int)ft_sqrt((double)n);
	if (chunk_size == 0)
		chunk_size = 1;
	return ((n + chunk_size - 1) / chunk_size);
}

int	is_in_chunk(t_push_swap_stat *stat, int val, int chunk_idx)
{
	int	num_chunks;
	int	chunk_size;
	int	rank;
	int	n;

	if (chunk_idx < 0)
		return (0);
	n = stat->element_cnt;
	rank = binary_search(stat->sorted, n, val);
	num_chunks = get_num_chunks(n);
	chunk_size = (n + num_chunks - 1) / num_chunks;
	if (chunk_idx == num_chunks - 1)
		return (rank >= chunk_idx * chunk_size && rank < n);
	return (rank >= chunk_idx * chunk_size
		&& rank < (chunk_idx + 1) * chunk_size);
}

int	get_chunk_cnt(t_push_swap_stat *stat, int chunk_idx, int c_sz)
{
	int	num_chunks;

	if (chunk_idx < 0)
		return (0);
	num_chunks = (stat->element_cnt + c_sz - 1) / c_sz;
	if (chunk_idx == num_chunks - 1)
		return (stat->element_cnt - chunk_idx * c_sz);
	return (c_sz);
}
