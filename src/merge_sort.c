/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 21:18:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 12:16:20 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

static void	copy_array(int *arr, int *tmp, int left, int right)
{
	int	i;

	i = left;
	while (i <= right)
	{
		arr[i] = tmp[i];
		i++;
	}
}

static void	merge(int *arr, int *tmp, int left, int right)
{
	int	i;
	int	j;
	int	k;
	int	mid;

	mid = left + (right - left) / 2;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}
	while (i <= mid)
		tmp[k++] = arr[i++];
	while (j <= right)
		tmp[k++] = arr[j++];
	copy_array(arr, tmp, left, right);
}

static void	merge_sort_helper(int *arr, int *tmp, int left, int right)
{
	int	mid;

	if (left < right)
	{
		mid = left + (right - left) / 2;
		merge_sort_helper(arr, tmp, left, mid);
		merge_sort_helper(arr, tmp, mid + 1, right);
		merge(arr, tmp, left, right);
	}
}

int	merge_sort(int *arr, int size)
{
	int	*tmp;

	if (size <= 1)
		return (1);
	if (!arr)
		return (0);
	tmp = (int *)malloc(sizeof(int) * size);
	if (!tmp)
		return (0);
	merge_sort_helper(arr, tmp, 0, size - 1);
	free(tmp);
	return (1);
}
