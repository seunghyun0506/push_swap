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
#include "push_swap_sort.h"
#include <complex.h>
#include <stdlib.h>

int			parse_stack(t_push_swap_stat *stat);
void		sort(t_push_swap_stat *stat);
static int	add_node(t_list **lst, int num);
static int	parse_integers(t_list **lst, const char *str);
static void	list_to_stack(t_push_swap_stat *stat, t_list **lst, int node_cnt);

void	sort(t_push_swap_stat *stat)
{
	stat->initial_disorder = compute_disorder(stat->stack_a);
	if (stat->option == 1)
		stat->selected_strategy = 1;
	else if (stat->option == 2)
		stat->selected_strategy = 2;
	else if (stat->option == 3)
		stat->selected_strategy = 3;
	else
	{
		if (stat->initial_disorder < 0.2)
			stat->selected_strategy = 1;
		else if (stat->initial_disorder < 0.5)
			stat->selected_strategy = 2;
		else
			stat->selected_strategy = 3;
	}
	if (stat->initial_disorder == 0.0)
		return ;
	if (stat->selected_strategy == 1)
		simple_sort(stat);
	else if (stat->selected_strategy == 2)
		medium_sort(stat);
	else if (stat->selected_strategy == 3)
		complex_sort(stat);
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
	{
		ft_lstclear(&list, free);
		return (0);
	}
	list_to_stack(stat, &list, cnt);
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
	int			err;
	const char	*pos;

	cnt = 0;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		num = str_to_int(str, &pos, &err);
		if (err || (*pos != '\0' && !ft_isspace(*pos)))
			return (ft_lstclear(lst, free), -1);
		if (!add_node(lst, num))
			return (ft_lstclear(lst, free), -1);
		cnt++;
		str = pos;
	}
	if (cnt == 0)
		return (-1);
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
