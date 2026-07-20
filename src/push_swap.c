/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:52:08 by slim              #+#    #+#             */
/*   Updated: 2026/07/09 13:52:08 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include "merge_sort.h"
#include "push_swap_sort.h"
#include <complex.h>
#include <stdlib.h>

int			parse_stack(t_push_swap_stat *stat);
void		sort(t_push_swap_stat *stat);
static int	parse_integers(t_list **lst, const char *str);
static void	list_to_stack(t_push_swap_stat *stat, t_list **lst, int node_cnt);

void	sort(t_push_swap_stat *stat)
{
	int	n;

	n = get_stack_size(stat->stack_a);
	if (stat->option == 1)
		simple_sort(stat);
	else if (stat->option == 2)
		medium_sort(stat);
	else if (stat->option == 3)
		complex_sort(stat);
	else
	{
		if (n <= 5)
			simple_sort(stat);
		else if (n <= 100)
			medium_sort(stat);
		else
			complex_sort(stat);
	}
}

int	parse_stack(t_push_swap_stat *stat)
{
	int			cnt;
	int			tmp;
	t_list		*list;

	cnt = 0;
	list = 0;
	while (stat->i < stat->argc)
	{
		tmp = parse_integers(&list, stat->argv[stat->i]);
		if (tmp < 0)
			return (0);
		cnt += tmp;
		stat->i++;
	}
	stat->stack_a = init_stack(cnt);
	stat->stack_b = init_stack(cnt);
	stat->sorted = (int *)malloc(sizeof(int) * cnt);
	if (!stat->stack_a || !stat->stack_b || !stat->sorted)
		return (ft_lstclear(&list, free), free(stat->sorted),
			free(stat->stack_a), free(stat->stack_b), 0);
	list_to_stack(stat, &list, cnt);
	merge_sort(stat->sorted, cnt);
	return (1);
}

static int	add_node(t_list **lst, int num)
{
	int		*tmp_int;
	t_list	*tmp;

	tmp_int = (int *)malloc(sizeof(int));
	if (!tmp_int)
		return (0);
	*tmp_int = num;
	tmp = ft_lstnew(tmp_int);
	if (!tmp)
	{
		free(tmp_int);
		return (0);
	}
	ft_lstadd_front(lst, tmp);
	return (1);
}

static int	parse_integers(t_list **lst, const char *str)
{
	int			num;
	int			cnt;
	const char	*pos;

	cnt = 0;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		num = ft_strtoi(str, &pos);
		if (str == pos || (*pos != '\0' && !ft_isspace(*pos)))
			return (ft_lstclear(lst, free), -1);
		if (!add_node(lst, num))
			return (ft_lstclear(lst, free), -1);
		cnt++;
		str = pos;
	}
	return (cnt);
}

static void	list_to_stack(t_push_swap_stat *stat, t_list **lst, int node_cnt)
{
	t_list	*list_tmp;
	int		i;

	i = node_cnt - 1;
	while (node_cnt--)
	{
		push_stack_data(stat->stack_a, *((int *)(*lst)->content));
		stat->sorted[i--] = *((int *)(*lst)->content);
		list_tmp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(list_tmp, free);
	}
}
