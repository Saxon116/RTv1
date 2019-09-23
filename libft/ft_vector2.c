/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <lucmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 09:44:52 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/10 13:47:46 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector2	*new_vector2(double x, double y)
{
	t_vector2	*vec;

	if (!(vec = malloc(sizeof(t_vector2))))
		return (NULL);
	vec->x = x;
	vec->y = y;
	return (vec);
}

t_vector2	*add_vector2(t_vector2 *u, t_vector2 *v, int free)
{
	t_vector2	*w;

	if (!u || !v)
		return (NULL);
	w = new_vector2(u->x + v->x, u->y + v->y);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

t_vector2	*sub_vector2(t_vector2 *u, t_vector2 *v, int free)
{
	t_vector2	*w;

	if (!u || !v)
		return (NULL);
	w = new_vector2(u->x - v->x, u->y - v->y);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

t_vector2	*mul_vector2(t_vector2 *u, t_vector2 *v, int free)
{
	t_vector2	*w;

	if (!u || !v)
		return (NULL);
	w = new_vector2(u->y * v->x - u->x * v->y, u->x * v->y - u->y - v->x);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

double		scal_vector2(t_vector2 *u, t_vector2 *v, int free)
{
	double	w;

	w = u->x * v->y + u->y * v->x;
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}
