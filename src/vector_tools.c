/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:10:21 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/07 16:01:23 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	vector3_norm(t_vector3 *v)
{
	return (sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
}

void	normalize_vector(t_vector3 *vec)
{
	double mag;

	mag = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
	if (mag == 0.0)
		mag = 1;
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
}

int		get_vector(t_vector3 *toset, char *input)
{
	char	**xyz;

	xyz = ft_strsplit(input, ',');
	if (ft_arraylength(xyz) != 3 && ft_arrayfree(xyz))
		return (0);
	toset->x = ft_atod(xyz[0]);
	toset->y = ft_atod(xyz[1]);
	toset->z = ft_atod(xyz[2]);
	ft_arrayfree(xyz);
	return (1);
}

void	invert_vector(t_vector3 *toinvert)
{
	toinvert->x = -toinvert->x;
	toinvert->y = -toinvert->y;
	toinvert->z = -toinvert->z;
}
