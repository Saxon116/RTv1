/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:20:40 by lucmarti          #+#    #+#             */
/*   Updated: 2019/04/15 10:26:12 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_size(t_matrix *m1, t_matrix *m2)
{
	if (!m1 || !m2 || !(m1->dim) || !(m2->dim))
		return (0);
	return (m1->dim->y == m2->dim->x);
}

static int	dot_product(t_matrix *m1, t_matrix *m2, int x, int y)
{
	int	res;
	int	i;
	int com;

	i = 0;
	com = m1->dim->y == m2->dim->x ? m1->dim->y : m1->dim->x;
	res = 0;
	while (i < com)
	{
		res += m1->mat[x][i] * m2->mat[i][y];
		++i;
	}
	return (res);
}

t_matrix	*mat_mul(t_matrix *m1, t_matrix *m2, int del)
{
	t_matrix	*r;
	t_vector2	pos;
	t_vector2	size;

	size.x = m1->dim->y == m2->dim->x ? m1->dim->x : m2->dim->x;
	size.y = m1->dim->y == m2->dim->x ? m2->dim->y : m2->dim->y;
	if (!m1 || !m2 || !check_size(m1, m2)
			|| !(r = mat_create(size.x, size.y)))
		return (NULL);
	pos.x = 0;
	while (pos.x < size.x && (pos.y = 0) == 0)
	{
		while (pos.y < size.y)
		{
			r->mat[pos.x][pos.y] = dot_product(m1, m2, pos.x, pos.y);
			++pos.y;
		}
		++pos.x;
	}
	if (del)
	{
		mat_free(m1);
		mat_free(m2);
	}
	return (r);
}
