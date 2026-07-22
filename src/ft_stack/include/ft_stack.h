/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 21:16:23 by slim              #+#    #+#             */
/*   Updated: 2026/05/12 21:16:23 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_H
# define FT_STACK_H

typedef struct s_stack
{
	int	*datas;
	int	capacity;
	int	top_index;
	int	bottom_index;
}	t_stack;

typedef enum e_op
{
	OP_NONE,
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
}	t_op;

t_stack	*init_stack(int capacity);
void	destroy_stack(t_stack *s);

int		push_stack_data(t_stack *s, int data);
int		pop_stack_data(t_stack *s, int *res);

int		rotate_stack(t_stack *s, t_op *op);
int		rotate_stacks(t_stack *s1, t_stack *s2, t_op *op);

int		rrotate_stack(t_stack *s, t_op *op);
int		rrotate_stacks(t_stack *s1, t_stack *s2, t_op *op);

int		swap_stack(t_stack *s, t_op *op);
int		swap_stacks(t_stack *s1, t_stack *s2, t_op *op);

int		push_stack(t_stack *from, t_stack *to, t_op *op);

int		is_stack_full(t_stack *s);
int		get_stack_top(t_stack *s, int *res);
int		get_stack_size(t_stack *s);
#endif
