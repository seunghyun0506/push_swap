/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:59:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/20 15:47:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_sort.h"
#include "libft.h"

int	medium_sort(t_push_swap_stat *stat)
{
	int	n;
	int	chunk_size;
	int	total_chunks;

	n = get_stack_size(stat->stack_a);
	if (n <= 3)
		return (small_sort(stat, stat->stack_a, stat->stack_b, n));
	chunk_size = (int)ft_sqrt((double)n);
	if (chunk_size == 0)
		chunk_size = 1;
	total_chunks = (n + chunk_size - 1) / chunk_size;
	divide_by_chunks(stat, chunk_size, total_chunks);
	return_to_a_by_chunk(stat, chunk_size, total_chunks);
	return (1);
}
