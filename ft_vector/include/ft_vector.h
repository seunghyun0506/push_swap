/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slim <slim@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:06:31 by slim              #+#    #+#             */
/*   Updated: 2026/07/16 14:13:04 by slim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

typedef struct s_vector
{
	int	*arr;
	int	idx;
	int	capacity;
} t_vector;

t_vector	*vecnew(int capacity);
void		vecadd_back(t_vector *v);
void		vecremove(t_vector *v, int idx);
void		vecdel(t_vector *v);
#endif
