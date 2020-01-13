/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 10:29:24 by lucmarti          #+#    #+#             */
/*   Updated: 2019/01/09 12:28:04 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		mat_display(t_matrix *mat)
{
	int		i;
	int		j;
	char	*str;

	if (!mat)
		return ;
	i = 0;
	while (i < mat->dim->x && (j = 0) == 0)
	{
		while (j < mat->dim->y)
		{
			str = ft_itoa(mat->mat[i][j]);
			ft_putstr(str);
			ft_putchar(' ');
			++j;
			ft_memdel((void **)&str);
		}
		ft_putchar('\n');
		++i;
	}
}

void		mat_free(t_matrix *matrix)
{
	int i;
	int j;

	if (!matrix || !(matrix->dim) || !(matrix->mat))
		return ;
	i = 0;
	while (i < matrix->dim->x && (j = 0) == 0)
	{
		ft_memdel((void **)&(matrix->mat[i]));
		++i;
	}
	ft_memdel((void **)&(matrix->mat));
	ft_memdel((void **)&(matrix->dim));
	ft_memdel((void **)&matrix);
}

static int	**mat_init(t_vector2 *dim)
{
	int	**cp;
	int	i;

	if (!(cp = (int **)malloc(sizeof(int *) * dim->x)))
		return (NULL);
	i = 0;
	while (i < dim->x)
	{
		if (!(cp[i] = (int *)malloc(sizeof(int) * dim->y)))
			return (NULL);
		ft_bzero(cp[i], dim->y);
		++i;
	}
	return (cp);
}

t_matrix	*mat_create(size_t lx, size_t ly)
{
	t_matrix	*matrix;
	t_vector2	*dim;

	if (!(matrix = malloc(sizeof(t_matrix))))
		return (NULL);
	if (!(dim = new_vector2(lx, ly)))
		return (NULL);
	if (!(matrix->mat = mat_init(dim)))
		return (NULL);
	matrix->dim = dim;
	return (matrix);
}
