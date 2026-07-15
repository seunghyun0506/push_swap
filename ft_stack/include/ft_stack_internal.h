/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 11:16:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/04 11:20:39 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_INTERNAL_H
# define FT_STACK_INTERNAL_H
# include "ft_stack.h"

int	next_idx(t_stack *s, int num);
int	prev_idx(t_stack *s, int num);
#endif
