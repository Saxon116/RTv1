/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:13:17 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/07 12:28:10 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	to check if 3 points are aligned and within a segment (a/b/c)
**		check if ab + bc = ac (use magnitude)
**	a is the start point (shadow origin)
**	b is the mid point (intersection hit)
**	c is the end point (light origin)
**	ac = shadow to light (dst[2])
**	ab = shadow to hit (dst[0])
**	bc = hit to light (dst[1]);
**	Furthermore we need to check that there is nothing between the intersection
**	and the shadow origin.
*/

static int		compare_ray(t_vector3 *to1, t_vector3 *to2, struct s_ray *from)
{
	t_vector3	hitpoint[3];
	double		dst[3];

	vector3_sub(to2, &from->org, &hitpoint[0]);
	vector3_sub(to1, to2, &hitpoint[1]);
	vector3_sub(to1, &from->org, &hitpoint[2]);
	dst[0] = vector3_norm(&hitpoint[0]);
	dst[1] = vector3_norm(&hitpoint[1]);
	dst[2] = vector3_norm(&hitpoint[2]);
	if (dst[0] + dst[1] == dst[2] || (dst[0] + dst[1] <= dst[2] + 0.0001
			&& dst[0] + dst[1] >= dst[2] - 0.0001))
		return (1);
	return (0);
}

/*
**	PROBLEM : we need to check the closet one on the line...
**	If two sphere are aligned between the shadow origin and the light
**	shadow won't necessarily add up
**	-
**	Should do :
**	compute shadowRay (origin and direction)
**	for each obj in the scene do :
**		if obj is obj from shadowRay or obj is light : continue
**		if obj intersect with shadow_ray do :
**			for each obj in the scene do :
**				get the closest intersection using the ray between light
**				and shadow origin
*/

static int		compare_obj(struct s_obj *x, struct s_obj *y, struct s_ray *src)
{
	t_vector3	hitpoint[2];
	double		dst[2];

	if (x == NULL)
		return (1);
	vector3_sub(&(x->hit), &(src->org), &hitpoint[0]);
	vector3_sub(&(y->hit), &(src->org), &hitpoint[1]);
	dst[0] = vector3_norm(&hitpoint[0]);
	dst[1] = vector3_norm(&hitpoint[1]);
	if (dst[0] < dst[1])
		return (0);
	return (1);
}

/*
**	IDEA : get all intersection that are between obj and light
**	sort them by dst. Closest one win
*/

void			compute_shadows(struct s_obj *obj[2], t_vector3 *hit
		, t_vector3 *color, struct s_display *dp)
{
	struct s_ray	shadow_ray;
	struct s_obj	*closest;
	int				i;

	i = -1;
	closest = NULL;
	shadow_ray.org = *hit;
	vector3_sub(&(obj[1]->org), &shadow_ray.org, &shadow_ray.dir);
	normalize_vector(&shadow_ray.dir);
	while (dp->objs[++i])
	{
		if (dp->objs[i] == obj[0] || dp->objs[i]->type == LIGHT)
			continue;
		if (dp->objs[i]->intersection(&shadow_ray, dp->objs[i]))
			if (compare_ray(&(obj[1]->org), &dp->objs[i]->hit, &shadow_ray))
				if (compare_obj(closest, dp->objs[i], &shadow_ray))
					closest = dp->objs[i];
	}
	if (closest && closest != obj[1])
	{
		color->x *= 0.;
		color->y *= 0.;
		color->z *= 0.;
	}
}
