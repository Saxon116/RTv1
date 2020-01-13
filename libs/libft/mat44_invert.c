/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat44_invert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:38:15 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/24 16:29:55 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		set_id(struct s_mat44 *mat)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (j == i)
				mat->rx[i][j] = 1;
			else
				mat->rx[i][j] = 0;
			++j;
		}
		++i;
	}
}

static void	gauss_elem(struct s_mat44 *mat, size_t i, size_t j)
{
	double	ratio;
	size_t	k;

	ratio = mat->x[j][i] / mat->x[i][i];
	k = 0;
	while (k < 4 * 2)
	{
		if (k < 4)
			mat->x[j][k] = mat->x[j][k] - ratio * mat->x[i][k];
		else
			mat->rx[j][k - 4] = mat->rx[j][k - 4] - ratio * mat->rx[i][k - 4];
		++k;
	}
}

static void	row_conversion(struct s_mat44 *mat)
{
	size_t	i;
	size_t	j;
	double	tmp;

	i = 0;
	while (i < 4)
	{
		tmp = mat->x[i][i];
		j = 0;
		while (j < 2 * 4)
		{
			if (j < 4)
				mat->x[i][j] = mat->x[i][j] / tmp;
			else
				mat->rx[i][j - 4] = mat->rx[i][j - 4] / tmp;
			++j;
		}
		++i;
	}
}

int			inv_procedure(struct s_mat44 *mat)
{
	size_t	i;
	size_t	j;

	set_id(mat);
	i = 0;
	while (i < 4)
	{
		if (mat->x[i][i] == 0.0)
			return (0);
		j = 0;
		while (j < 4)
		{
			if (i != j)
				gauss_elem(mat, i, j);
			++j;
		}
		++i;
	}
	row_conversion(mat);
	return (1);
}
