/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:45:58 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/07 12:02:03 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_cone(struct s_ray *ray, struct s_obj *cone)
{
	double		ret;
	double		dv;
	double		x[3];
	double		theta_rad;
	t_vector3	co;

	dv = vector3_scal(&ray->dir, &cone->dir);
	theta_rad = cone->dim[2] * (M_PI / 180);
	x[0] = pow(dv, 2) - pow(cos(theta_rad), 2);
	vector3_sub(&ray->org, &cone->org, &co);
	x[1] = 2 * (dv * vector3_scal(&co, &cone->dir)
			- vector3_scal(&ray->dir, &co) * pow(cos(theta_rad), 2));
	x[2] = pow(vector3_scal(&co, &cone->dir), 2)
		- vector3_scal(&co, &co) * pow(cos(theta_rad), 2);
	if (!(ret = solve_quadratic(x[0], x[1], x[2], &ret)))
		return (0);
	cone->hit.x = ray->org.x + ray->dir.x * ret;
	cone->hit.y = ray->org.y + ray->dir.y * ret;
	cone->hit.z = ray->org.z + ray->dir.z * ret;
	return (1);
}

void	cone_set_mod(double ctr, double dir, double axis
		, double *mod)
{
	*mod = 0;
	if (dir > 0.0)
		*mod = axis < ctr ? -1 : 1;
	else if (dir < 0.0)
		*mod = axis < ctr ? 1 : -1;
}

void	cone_render(void *dp, struct s_obj *cone
		, size_t x, size_t y)
{
	double		mod[4];
	double		k_dist;
	t_vector3	cth;
	t_vector3	n;
	t_vector3	color;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	vector3_sub(&cone->hit, &cone->org, &cth);
	k_dist = vector3_norm(&cth);
	cone_set_mod(cone->org.x, cone->dir.x, cone->hit.x, &(mod[0]));
	cone_set_mod(cone->org.y, cone->dir.y, cone->hit.y, &(mod[1]));
	cone_set_mod(cone->org.z, cone->dir.z, cone->hit.z, &(mod[2]));
	n.x = cone->org.x + (cone->dir.x * k_dist * mod[0]);
	n.y = cone->org.y + (cone->dir.y * k_dist * mod[1]);
	n.z = cone->org.z + (cone->dir.z * k_dist * mod[2]);
	vector3_sub(&cone->hit, &n, &n);
	normalize_vector(&n);
	compute_light(cone, (struct s_display *)dp, &n, &color);
	plot(x, y, (struct s_display *)dp, &color);
}
