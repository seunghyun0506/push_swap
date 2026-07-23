/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:57:30 by slim              #+#    #+#             */
/*   Updated: 2026/07/21 07:00:39 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

char				*get_next_line(int fd);
static t_gnl_node	**init(t_gnl_str *str, int fd,
						t_gnl_node **head);
static void			destroy(t_gnl_str *str, t_gnl_node **curr, char *ret);
char				*ft_strndup(char *arr, int size);
int					fill_buffer(int fd, t_gnl_buf *buf);
void				gnl_resize(t_gnl_str *str);
int					gnl_add_str(t_gnl_str *res, t_gnl_buf *buf);
t_gnl_node			**gnl_add_node(t_gnl_node **head, int fd);
void				gnl_del_node(t_gnl_node	**node);
t_gnl_node			**gnl_search_node(t_gnl_node **head, int fd);

char	*get_next_line(int fd)
{
	t_gnl_str			str;
	static t_gnl_node	*head;
	t_gnl_node			**curr;
	char				*ret;

	curr = init(&str, fd, &head);
	if (!curr)
		return (NULL);
	ret = 0;
	while (1)
	{
		if (!fill_buffer(fd, &(*curr)->buf))
			break ;
		if (gnl_add_str(&str, &(*curr)->buf) != 0)
			break ;
	}
	if (!(str.idx == 0 || (*curr)->buf.capacity < 0))
		ret = ft_strndup(str.arr, str.idx);
	return (destroy(&str, curr, ret), ret);
}

t_gnl_node	**init(t_gnl_str *str, int fd,
						t_gnl_node **head)
{
	t_gnl_node	**curr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	curr = gnl_search_node(head, fd);
	if (curr == NULL)
		curr = gnl_add_node(head, fd);
	if (curr == NULL)
		return (0);
	str->arr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	str->idx = 0;
	str->capacity = BUFFER_SIZE;
	if ((*curr)->buf.buffer == NULL)
	{
		(*curr)->buf.buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
		(*curr)->buf.capacity = 0;
		(*curr)->buf.idx = 0;
	}
	if ((*curr)->buf.buffer == NULL || str->arr == NULL)
	{
		destroy(str, curr, NULL);
		return (NULL);
	}
	return (curr);
}

static void	destroy(t_gnl_str *str, t_gnl_node **curr, char *ret)
{
	free(str->arr);
	if ((*curr)->buf.idx >= (*curr)->buf.capacity || ret == NULL)
	{
		free((*curr)->buf.buffer);
		(*curr)->buf.buffer = 0;
		gnl_del_node(curr);
	}
}

char	*ft_strndup(char *arr, int size)
{
	char	*ret;
	int		index;

	index = 0;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	while (index < size)
	{
		ret[index] = arr[index];
		index++;
	}
	ret[index] = '\0';
	return (ret);
}

int	fill_buffer(int fd, t_gnl_buf *buf)
{
	if (buf->idx >= buf->capacity)
	{
		buf->capacity = read(fd, buf->buffer, BUFFER_SIZE);
		buf->idx = 0;
		if (buf->capacity <= 0)
			return (0);
	}
	return (1);
}
