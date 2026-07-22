/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 12:30:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 03:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "ft_stack_internal.h"
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

void	selection_sort_to_b(t_push_swap_stat *stat)
{
	int		idx;
	int		sz;
	t_op	op;

	while (get_stack_size(stat->stack_b) > 0 && !stat->op_buffer->err)
	{
		idx = find_max_idx_stack(stat->stack_b);
		sz = get_stack_size(stat->stack_b);
		if (idx > sz / 2)
			idx -= sz;
		rotate_n(stat, stat->stack_b, idx);
		op = OP_PA;
		push_stack(stat->stack_b, stat->stack_a, &op);
		store_op(stat->op_buffer, op);
	}
}
