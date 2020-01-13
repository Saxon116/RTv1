/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 09:44:52 by lucmarti          #+#    #+#             */
/*   Updated: 2019/01/16 12:07:56 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dvector2	*new_dvector2(double x, double y)
{
	t_dvector2	*vec;

	if (!(vec = malloc(sizeof(t_dvector2))))
		return (NULL);
	vec->x = x;
	vec->y = y;
	return (vec);
}

t_dvector2	*add_dvector2(t_dvector2 *u, t_dvector2 *v, int free)
{
	t_dvector2	*w;

	if (!u || !v)
		return (NULL);
	w = new_dvector2(u->x + v->x, u->y + v->y);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

t_dvector2	*sub_dvector2(t_dvector2 *u, t_dvector2 *v, int free)
{
	t_dvector2	*w;

	if (!u || !v)
		return (NULL);
	w = new_dvector2(u->x - v->x, u->y - v->y);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

t_dvector2	*mul_dvector2(t_dvector2 *u, t_dvector2 *v, int free)
{
	t_dvector2	*w;

	if (!u || !v)
		return (NULL);
	w = new_dvector2(u->y * v->x - u->x * v->y, u->x * v->y - u->y - v->x);
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}

int			scal_dvector2(t_dvector2 *u, t_dvector2 *v, int free)
{
	int	w;

	w = u->x * v->y + u->y * v->x;
	if (free == 0)
		return (w);
	ft_memdel((void **)&u);
	ft_memdel((void **)&v);
	return (w);
}
