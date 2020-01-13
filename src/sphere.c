/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:41:24 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/10 13:58:37 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_sphere(struct s_ray *ray, struct s_obj *sphere)
{
	double		d[3];
	double		x[3];
	t_vector3	res;

	vector3_sub(&(ray->org), &(sphere->org), &(res));
	x[0] = vector3_scal(&(ray->dir), &(ray->dir));
	x[1] = 2 * vector3_scal(&res, &(ray->dir));
	x[2] = vector3_scal(&res, &res) - sphere->dim[2] * sphere->dim[2];
	if (!(d[0] = solve_quadratic(x[0], x[1], x[2], &d[0])))
		return (0);
	sphere->hit.x = ray->org.x + ray->dir.x * d[0];
	sphere->hit.y = ray->org.y + ray->dir.y * d[0];
	sphere->hit.z = ray->org.z + ray->dir.z * d[0];
	return (1);
}

void	sphere_render(void *dp_, struct s_obj *sphere
		, size_t x, size_t y)
{
	t_vector3	hit[3];
	t_vector3	color;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	hit[0] = sphere->hit;
	vector3_sub(&hit[0], &(sphere->org), &hit[2]);
	normalize_vector(&(hit[2]));
	compute_light(sphere, (struct s_display *)dp_, &hit[2], &color);
	plot(x, y, (struct s_display *)dp_, &color);
}
