/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:16:23 by slim              #+#    #+#             */
/*   Updated: 2026/05/12 21:16:23 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FT_STACK_H
#define FT_STACK_H

typedef struct s_stack
{
	int	*datas;
	int	capacity;
	int	top_index;
	int	bottom_index;
}	t_stack;

t_stack	*init_stack(int	capacity);
void	destroy_stack(t_stack *s);
int		push_stack_data(t_stack *s, int data);
int		pop_stack_data(t_stack *s, int *res);

int		rotate_stack(t_stack *s);
int		rotate_stacks(t_stack *s1, t_stack *s2);

int		rrotate_stack(t_stack *s);
int		rrotate_stacks(t_stack *s1, t_stack *s2);

int		swap_stack(t_stack *s);
int		swap_stacks(t_stack *s1, t_stack *s2);

int		is_stack_empty(t_stack *s);
int		is_stack_full(t_stack *s);
int		get_stack_top(t_stack *s, int *res);
int		get_stack_size(t_stack *s);
#endif
