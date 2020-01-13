/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 10:50:01 by lucmarti          #+#    #+#             */
/*   Updated: 2019/04/15 10:26:47 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_size(t_matrix *m1, t_matrix *m2)
{
	if (!m1 || !m2 || !(m1->dim) || !(m2->dim))
		return (0);
	return (m1->dim->x == m2->dim->x && m1->dim->y == m2->dim->y);
}

t_matrix	*mat_add(t_matrix *m1, t_matrix *m2, int del)
{
	t_matrix	*res;
	int			i;
	int			j;

	if (!m1 || !m2 || !check_size(m1, m2)
			|| !(res = mat_create(m1->dim->x, m2->dim->y)))
		return (NULL);
	i = 0;
	while (i < m1->dim->x)
	{
		j = 0;
		while (j < m1->dim->y)
		{
			res->mat[i][j] = m1->mat[i][j] + m2->mat[i][j];
			++j;
		}
		++i;
	}
	if (del)
	{
		mat_free(m1);
		mat_free(m2);
	}
	return (res);
}

t_matrix	*mat_sub(t_matrix *m1, t_matrix *m2, int del)
{
	t_matrix	*res;
	int			i;
	int			j;

	if (!m1 || !m2 || !check_size(m1, m2)
			|| !(res = mat_create(m1->dim->x, m2->dim->y)))
		return (NULL);
	i = 0;
	while (i < m1->dim->x)
	{
		j = 0;
		while (j < m1->dim->y)
		{
			res->mat[i][j] = m1->mat[i][j] - m2->mat[i][j];
			++j;
		}
		++i;
	}
	if (del)
	{
		mat_free(m1);
		mat_free(m2);
	}
	return (res);
}

t_matrix	*mat_mscal(t_matrix *m1, int scal, int del)
{
	t_matrix	*res;
	int			i;
	int			j;

	if (!m1 || !(res = mat_create(m1->dim->x, m1->dim->y)))
		return (NULL);
	i = 0;
	while (i < m1->dim->x)
	{
		j = 0;
		while (j < m1->dim->y)
		{
			res->mat[i][j] = m1->mat[i][j] * scal;
			++j;
		}
		++i;
	}
	if (del)
		mat_free(m1);
	return (res);
}

t_matrix	*mat_transpose(t_matrix *m1, int del)
{
	t_matrix	*res;
	int			i;
	int			j;

	if (!m1 || !(res = mat_create(m1->dim->x, m1->dim->y)))
		return (NULL);
	i = 0;
	while (i < m1->dim->x)
	{
		j = 0;
		while (j < m1->dim->y)
		{
			res->mat[j][i] = m1->mat[i][j];
			++j;
		}
		++i;
	}
	if (del)
		mat_free(m1);
	return (res);
}
