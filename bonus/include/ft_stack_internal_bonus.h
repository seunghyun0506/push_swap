/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_internal_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 11:16:00 by slim              #+#    #+#             */
/*   Updated: 2026/07/23 11:00:00 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_INTERNAL_BONUS_H
# define FT_STACK_INTERNAL_BONUS_H

# include "ft_stack_bonus.h"

int	next_idx(t_stack *s, int num);
int	prev_idx(t_stack *s, int num);

#endif
