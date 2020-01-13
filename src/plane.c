/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:43:05 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/10 13:46:19 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	intersect_plane(struct s_ray *ray, struct s_obj *plane)
{
	double		t;
	double		a;
	double		b;
	t_vector3	res;

	vector3_sub(&ray->org, &plane->org, &res);
	a = vector3_scal(&res, &plane->dir);
	b = vector3_scal(&ray->dir, &plane->dir);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t = -a / b;
	plane->hit.x = ray->org.x + ray->dir.x * t;
	plane->hit.y = ray->org.y + ray->dir.y * t;
	plane->hit.z = ray->org.z + ray->dir.z * t;
	return (t > 0 ? t : 0);
}

void	plane_render(void *dp_, struct s_obj *plane
		, size_t x, size_t y)
{
	struct s_display	*dp;
	t_vector3			view_normal;
	t_vector3			color;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	dp = (struct s_display *)dp_;
	vector3_sub(&plane->hit, &plane->org, &view_normal);
	normalize_vector(&view_normal);
	compute_light(plane, dp, &view_normal, &color);
	plot(x, y, dp, &color);
}
