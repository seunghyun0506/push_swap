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

# include "ft_vector.h"

typedef struct s_op_buffer
{
	t_vector	*ops;
}	t_op_buffer;

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

t_op_buffer	*init_op_buffer(void);
void		store_op(t_op_buffer *buffer, t_op op);
void		free_op_buffer(t_op_buffer *buffer);
void		print_op_buffer(t_op_buffer *buffer);

#endif
