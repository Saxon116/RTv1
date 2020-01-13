/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 09:34:42 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/10 13:55:55 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		intersect_cylinder(struct s_ray *ray, struct s_obj *cylinder)
{
	t_vector3		midray;
	double			a;
	double			b;
	double			c;
	double			d;

	vector3_sub(&ray->org, &cylinder->org, &midray);
	a = vector3_scal(&ray->dir, &cylinder->dir);
	a = vector3_scal(&ray->dir, &ray->dir) - a * a;
	b = 2 * (vector3_scal(&ray->dir, &midray)
			- vector3_scal(&ray->dir, &cylinder->dir)
			* vector3_scal(&midray, &cylinder->dir));
	c = vector3_scal(&midray, &cylinder->dir);
	c = vector3_scal(&midray, &midray) - c * c - pow(cylinder->dim[2], 2);
	if (!(d = solve_quadratic(a, b, c, &d)))
		return (0);
	cylinder->hit.x = ray->org.x + ray->dir.x * d;
	cylinder->hit.y = ray->org.y + ray->dir.y * d;
	cylinder->hit.z = ray->org.z + ray->dir.z * d;
	return (1);
}

static void	cylinder_set_mod(double ctr, double dir, double axis
		, double *mod)
{
	*mod = 0;
	if (dir > 0.)
		*mod = axis < ctr ? -1 : 1;
	else if (dir < 0.)
		*mod = axis < ctr ? 1 : -1;
}

static void	cylinder_draw(struct s_display *dp, struct s_obj *cylinder
		, size_t c[2], t_vector3 v[2])
{
	vector3_sub(&cylinder->hit, &v[0], &v[0]);
	normalize_vector(&v[0]);
	compute_light(cylinder, dp, &v[0], &v[1]);
	plot(c[0], c[1], dp, &v[1]);
}

void		cylinder_render(void *dp_, struct s_obj *cylinder
		, size_t x, size_t y)
{
	double		mod[4];
	t_vector3	n;
	t_vector3	cth;
	t_vector3	color;
	t_vector3	norg;

	color.x = 0;
	color.y = 0;
	color.z = 0;
	norg.x = cylinder->org.x + cylinder->dir.x * 9999;
	norg.y = cylinder->org.y + cylinder->dir.y * 9999;
	norg.z = cylinder->org.z + cylinder->dir.z * 9999;
	cylinder_set_mod(norg.x, cylinder->dir.x, cylinder->hit.x, &(mod[0]));
	cylinder_set_mod(norg.y, cylinder->dir.y, cylinder->hit.y, &(mod[1]));
	cylinder_set_mod(norg.z, cylinder->dir.z, cylinder->hit.z, &(mod[2]));
	vector3_sub(&cylinder->hit, &norg, &cth);
	mod[3] = vector3_norm(&cth);
	if (mod[3] < cylinder->dim[2])
		mod[3] = 0;
	else
		mod[3] = sqrt((mod[3] * mod[3]) - pow(cylinder->dim[2], 2));
	n.x = norg.x + cylinder->dir.x * mod[3] * mod[0];
	n.y = norg.y + cylinder->dir.y * mod[3] * mod[1];
	n.z = norg.z + cylinder->dir.z * mod[3] * mod[2];
	cylinder_draw(dp_, cylinder, (size_t[2]){x, y}, (t_vector3[2]){n, color});
}
