/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:38:03 by nkellum           #+#    #+#             */
/*   Updated: 2019/11/06 14:34:02 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double intersect_plane(t_ray *ray, t_ray *plane)
{
    // assuming vectors are all normalized

    double denom = scal_vector3(plane->dir, ray->dir, 0);
    if (denom > 1e-6) {
        t_vector3 *p0l0 = sub_vector3(plane->pos, ray->pos, 0);
        double t = scal_vector3(p0l0, plane->dir, 0) / denom;
        return (t);
    }
    return 0;
}

t_ray *add_plane(t_vector3 *pos, t_vector3 *dir, int id)
{
	t_ray *plane;

	if ((plane = malloc(sizeof(t_ray))) == NULL)
		return (0);
	plane->pos = pos;
	plane->dir = dir;
	plane->dir->x *= -1;
	plane->dir->y *= -1;
	plane->dir->z *= -1;
	plane->id = id;
	plane->next = NULL;
	return (plane);
}

t_vector2 *check_plane_intersections(t_ray *eye, t_ray *plane_list)
{
	double t;
	double dist;
	t_ray *plane_hit;

	t = 0;
	dist = 0;
	plane_hit = NULL;
	while(plane_list)
	{
		dist = intersect_plane(eye, plane_list);
		if(dist > 1)
		{
			if(t == 0)
			{
				t = dist;
				plane_hit = plane_list;
			}
			else if(dist < t)
			{
				plane_hit = plane_list;
				t = dist;
			}
		}
		plane_list = plane_list->next;
	}
	if(plane_hit)
		return (new_vector2(t, plane_hit->id));
	else
		return (NULL);
}

t_vector3 *get_plane_color(double t, t_ray *eye, t_ray *plane, t_ray *light_point, t_sphere *sphere_list)
{
	t_vector3 *hit_point;
	t_vector3 *hit_line;
	t_ray	*shadow_ray;

	if ((shadow_ray = malloc(sizeof(t_ray))) == NULL)
		return (0);


	hit_line = new_vector3(eye->dir->x * t,
	eye->dir->y * t, eye->dir->z * t);
	hit_point = add_vector3(eye->pos, hit_line, 0);

	t_vector3 *light_p_dist = sub_vector3(light_point->pos, hit_point, 0);
	double mag = sqrt(pow(light_p_dist->x, 2) + pow(light_p_dist->y, 2) + pow(light_p_dist->z, 2));
	int c = ceil(cos(hit_point->z)) * ceil(cos(hit_point->x));
	if(ceil(cos(hit_point->z)) == 0 && ceil(cos(hit_point->x)) == 0)
		c = 1;
	int r = c * 255;
	int g = c * 255;
	int b = c * 255;
	t_vector3 *object_color = new_vector3(r, g, b);

	object_color->x *= light_point->brightness / (4 * M_PI * pow(mag, 2));
	object_color->y *= light_point->brightness / (4 * M_PI * pow(mag, 2));
	object_color->z *= light_point->brightness / (4 * M_PI * pow(mag, 2));

	object_color->x = ft_constrain(object_color->x, 0, 255);
	object_color->y = ft_constrain(object_color->y, 0, 255);
	object_color->z = ft_constrain(object_color->z, 0, 255);

	normalize(light_p_dist);
	shadow_ray->pos = hit_point;
	shadow_ray->dir = light_p_dist;

	while(sphere_list)
	{
		double shadow_intersect = intersect(shadow_ray, sphere_list);
		if(shadow_intersect)
		{
			object_color->x *= 0.5;
			object_color->y *= 0.5;
			object_color->z *= 0.5;
		}
		sphere_list = sphere_list->next;
	}
	return (object_color);
}
