/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 12:51:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/19 12:51:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_BUFFER_H
# define OP_BUFFER_H

# include "ft_stack.h"

typedef struct s_op_buffer
{
	t_op	*arr;
	int		idx;
	int		capacity;
	int		err;
}	t_op_buffer;

t_op_buffer	*init_op_buffer(void);
void		store_op(t_op_buffer *buffer, t_op op);
void		free_op_buffer(t_op_buffer *buffer);
void		print_op_buffer(t_op_buffer *buffer);

#endif
