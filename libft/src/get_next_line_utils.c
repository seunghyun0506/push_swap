/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:19:17 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 06:59:41 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		gnl_resize(t_gnl_str *str);
int			gnl_add_str(t_gnl_str *res, t_gnl_buf *buf);
t_gnl_node	**gnl_add_node(t_gnl_node	**head, int fd);
void		gnl_del_node(t_gnl_node	**node);
t_gnl_node	**gnl_search_node(t_gnl_node **head, int fd);

void	gnl_resize(t_gnl_str *str)
{
	char	*new_str;
	int		index;

	new_str = (char *)malloc(sizeof(char) * ((str->capacity) * 2 + 1));
	if (new_str == 0)
	{
		free(str->arr);
		str->arr = NULL;
		str->idx = 0;
		return ;
	}
	index = 0;
	while (index < str->idx)
	{
		new_str[index] = str->arr[index];
		index++;
	}
	new_str[index] = '\0';
	free(str->arr);
	str->arr = new_str;
	str->capacity *= 2;
}

int	gnl_add_str(t_gnl_str *res, t_gnl_buf *buf)
{
	int	tmp;

	tmp = buf->idx;
	while (tmp < buf->capacity)
	{
		if (buf->buffer[tmp++] == '\n')
			break ;
	}
	tmp--;
	if (tmp - buf->idx >= res->capacity - res->idx)
		gnl_resize(res);
	if (res->arr == NULL)
		return (-1);
	while (buf->idx <= tmp)
	{
		res->arr[res->idx] = buf->buffer[buf->idx];
		res->idx++;
		buf->idx++;
	}
	res->arr[res->idx] = '\0';
	return (buf->buffer[tmp] == '\n'
		|| (buf->capacity < BUFFER_SIZE && buf->idx >= buf->capacity));
}

t_gnl_node	**gnl_add_node(t_gnl_node	**head, int fd)
{
	t_gnl_node	*node;

	node = (t_gnl_node *)malloc(sizeof(t_gnl_node));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->buf.buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	if (node->buf.buffer == NULL)
	{
		free(node);
		return (NULL);
	}
	node->buf.idx = 0;
	node->buf.capacity = 0;
	node->next = *head;
	*head = node;
	return (head);
}

void	gnl_del_node(t_gnl_node	**node)
{
	t_gnl_node	*tmp;

	if (*node == NULL)
		return ;
	tmp = *node;
	*node = tmp->next;
	free(tmp);
}

t_gnl_node	**gnl_search_node(t_gnl_node **head, int fd)
{
	while (*head != NULL)
	{
		if ((*head)->fd == fd)
			return (head);
		head = &((*head)->next);
	}
	return (NULL);
}
