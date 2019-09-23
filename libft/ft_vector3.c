/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <lucmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 09:44:52 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/19 18:38:13 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3	*new_vector3(double x, double y, double z)
{
	t_vector3	*vec;

	if (!(vec = malloc(sizeof(t_vector3))))
		return (NULL);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vector3	*add_vector3(t_vector3 *u, t_vector3 *v, int free)
{
	t_vector3	*w;

	if (!u || !v)
		return (NULL);
	w = new_vector3(u->x + v->x, u->y + v->y, u->z + v->z);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

t_vector3	*sub_vector3(t_vector3 *u, t_vector3 *v, int free)
{
	t_vector3	*w;

	if (!u || !v)
		return (NULL);
	w = new_vector3(u->x - v->x, u->y - v->y, u->z - v->z);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

t_vector3	*mul_vector3(t_vector3 *u, t_vector3 *v, int free)
{
	t_vector3	*w;

	if (!u || !v)
		return (NULL);
	w = new_vector3(u->y * v->z - u->z * v->y, u->z * v->x - u->x - v->z,
			u->x * v->y - u->y * v->x);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

double		scal_vector3(t_vector3 *u, t_vector3 *v, int free)
{
	double	w;

	w = u->x * v->x + u->y * v->y + u->z * v->z;
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}
