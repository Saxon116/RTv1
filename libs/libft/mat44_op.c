/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat44_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:41:11 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/07 10:59:54 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	mat44_mvec(struct s_mat44 *matrix, t_vector3 *v, t_vector3 *toset)
{
	t_vector3	res;

	res.x = v->x * matrix->x[0][0] + v->y * matrix->x[1][0]
		+ v->z * matrix->x[2][0];
	res.y = v->x * matrix->x[0][1] + v->y * matrix->x[1][1]
		+ v->z * matrix->x[2][1];
	res.z = v->x * matrix->x[0][2] + v->y * matrix->x[1][2]
		+ v->z * matrix->x[2][2];
	toset->x = res.x;
	toset->y = res.y;
	toset->z = res.z;
}

void	mat44_vvec(struct s_mat44 *matrix, t_vector3 *v, t_vector3 *toset)
{
	t_vector3	res;
	double		w;

	res.x = v->x * matrix->x[0][0] + v->y * matrix->x[1][0]
		+ v->z * matrix->x[2][0] + matrix->x[3][0];
	res.y = v->x * matrix->x[0][1] + v->y * matrix->x[1][1]
		+ v->z * matrix->x[2][1] + matrix->x[3][1];
	res.z = v->x * matrix->x[0][2] + v->y * matrix->x[1][2]
		+ v->z * matrix->x[2][2] + matrix->x[3][2];
	w = v->x * matrix->x[0][3] + v->y * matrix->x[1][3]
		+ v->z * matrix->x[2][3] + matrix->x[3][3];
	toset->x = res.x / w;
	toset->y = res.y / w;
	toset->z = res.z / w;
}

void	mat44_mscal(struct s_mat44 *matrix, double scal)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix->x[i][j] = matrix->x[i][j] * scal;
			++j;
		}
		++i;
	}
}

void	mat44_transpose(struct s_mat44 *matrix, struct s_mat44 *res)
{
	struct s_mat44	tmp;
	size_t			i[2];

	i[0] = 0;
	while (i[0] < 4)
	{
		i[1] = 0;
		while (i[1] < 4)
		{
			tmp.x[i[1]][i[0]] = matrix->x[i[0]][i[1]];
			++(i[1]);
		}
		++(i[0]);
	}
	i[0] = 0;
	while (i[0] < 4)
	{
		i[1] = 0;
		while (i[1] < 4)
		{
			res->x[i[0]][i[1]] = tmp.x[i[0]][i[1]];
			++(i[1]);
		}
		++(i[0]);
	}
}
