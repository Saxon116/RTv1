/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:53:38 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/07 16:11:04 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_x(t_vector3 *org, double a)
{
	t_vector3 r;

	r.x = org->x;
	r.y = org->y * cos(a) - org->z * sin(a);
	r.z = org->y * sin(a) + org->z * cos(a);
	org->x = r.x;
	org->y = r.y;
	org->z = r.z;
}

void	rotate_y(t_vector3 *org, double a)
{
	t_vector3 r;

	r.x = org->x * cos(a) + org->z * sin(a);
	r.y = org->y;
	r.z = org->z * cos(a) - org->x * sin(a);
	org->x = r.x;
	org->y = r.y;
	org->z = r.z;
}

void	rotate_z(t_vector3 *org, double a)
{
	t_vector3 r;

	r.x = org->x * cos(a) - org->y * sin(a);
	r.y = org->x * sin(a) + org->y * cos(a);
	r.z = org->z;
	org->x = r.x;
	org->y = r.y;
	org->z = r.z;
}

void	rotate_xyz(t_vector3 *org, t_vector3 *rot)
{
	(void)org;
	(void)rot;
	rotate_x(org, rot->x * (M_PI / 180));
	rotate_y(org, rot->y * (M_PI / 180));
	rotate_z(org, rot->z * (M_PI / 180));
}
