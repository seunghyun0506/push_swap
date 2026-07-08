/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 02:02:08 by slim              #+#    #+#             */
/*   Updated: 2026/07/08 02:02:08 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stack.h"
#include "push_swap_stat.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	parse_flag(t_push_swap_stat *stat);
static int	parse_stack(t_push_swap_stat *stat);
static int	parse_integers(t_list **lst, const char *str);
static void	sort(t_push_swap_stat *stat);

int	main(int argc, char **argv)
{
	t_push_swap_stat	stat;

	if (argc <= 1)
		return (write(1, "Error\n", 6), 1);
	init_push_swap_stat(&stat, argc, argv);
	if (!parse_flag(&stat))
		return (write(1, "Error\n", 6), 1);
	if (!parse_stack(&stat))
		return (write(1, "Error\n", 6), 1);
	sort(&stat);
}

static int	parse_flag(t_push_swap_stat *stat)
{
	int	opt_cnt;
	int	bench_cnt;

	opt_cnt = 0;
	bench_cnt = 0;
	while (stat->i < stat->argc)
	{
		if (ft_strcmp(stat->argv[stat->i], "--simple") == 0 && ++opt_cnt)
			stat->option = 1;
		else if (ft_strcmp(stat->argv[stat->i], "--medium") == 0 && ++opt_cnt)
			stat->option = 2;
		else if (ft_strcmp(stat->argv[stat->i], "--complex") == 0 && ++opt_cnt)
			stat->option = 3;
		else if (ft_strcmp(stat->argv[stat->i], "--adaptive") == 0 && ++opt_cnt)
			stat->option = 0;
		else if (ft_strcmp(stat->argv[stat->i], "--bench") == 0 && ++bench_cnt)
			stat->bench = 1;
		else
			break ;
		stat->i++;
	}
	if (opt_cnt > 1 || bench_cnt > 1)
		return (0);
	return (1);
}

static void	sort(t_push_swap_stat *stat)
{
}

static int	parse_stack(t_push_swap_stat *stat)
{
	int			cnt;
	int			tmp;
	t_list		*list;
	t_list		*list_tmp;

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
	if (!stat->stack_a || !stat->stack_b)
		return (ft_lstclear(&list, free),
			free(stat->stack_a), free(stat->stack_b), 0);
	while (cnt--)
	{
		push_stack_data(stat->stack_a, *((int *)list->content));
		list_tmp = list;
		list = list->next;
		ft_lstdelone(list_tmp, free);
	}
	return (1);
}

static int	parse_integers(t_list **lst, const char *str)
{
	int			num;
	int			cnt;
	const char	*pos;
	int			*tmp_int;
	t_list		*tmp;

	cnt = 0;
	while (*str != '\0')
	{
		num = ft_strtoi(str, &pos);
		if (str == pos
			|| (*pos != '\0' && !ft_isspace(*pos)) || !ft_isdigit(*(pos - 1)))
			return (ft_lstclear(lst, free), -1);
		tmp_int = (int *)malloc(sizeof(int));
		if (!tmp_int)
			return (ft_lstclear(lst, free), -1);
		*tmp_int = num;
		tmp = ft_lstnew(tmp_int);
		if (!tmp)
			return (free(tmp_int), ft_lstclear(lst, free), -1);
		ft_lstadd_front(lst, tmp);
		cnt++;
		str = pos;
	}
	return (cnt);
}
