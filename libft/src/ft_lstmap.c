/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:55:02 by slim              #+#    #+#             */
/*   Updated: 2026/04/08 17:52:23 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;
	void	*f_res;

	res = 0;
	f_res = 0;
	while (lst != NULL)
	{
		f_res = f(lst->content);
		if (!f_res)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		tmp = ft_lstnew(f_res);
		if (tmp == NULL)
		{
			del(f_res);
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, tmp);
		lst = lst->next;
	}
	return (res);
}
