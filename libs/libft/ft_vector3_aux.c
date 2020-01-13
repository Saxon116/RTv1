/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:07:45 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/23 13:26:49 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_initvector3(t_vector3 *init, double x, double y, double z)
{
	init->x = x;
	init->y = y;
	init->z = z;
}

void			vector3_add(t_vector3 *u, t_vector3 *v, t_vector3 *ret)
{
	if (!u || !v)
		return ;
	ft_initvector3(ret, u->x + v->x, u->y + v->y, u->z + v->z);
}

void			vector3_sub(t_vector3 *u, t_vector3 *v, t_vector3 *ret)
{
	if (!u || !v)
		return ;
	ft_initvector3(ret, u->x - v->x, u->y - v->y, u->z - v->z);
}

void			vector3_mul(t_vector3 *u, t_vector3 *v, t_vector3 *ret)
{
	if (!u || !v)
		return ;
	ft_initvector3(ret, u->y * v->z - u->z * v->y, u->z * v->x - u->x - v->z,
			u->x * v->y - u->y * v->x);
}

long double		vector3_scal(t_vector3 *u, t_vector3 *v)
{
	long double	w;

	if (!u || !v)
		return (0);
	w = u->x * v->x + u->y * v->y + u->z * v->z;
	return (w);
}
