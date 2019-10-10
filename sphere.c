/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:35:07 by nkellum           #+#    #+#             */
/*   Updated: 2019/10/10 19:29:55 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector3 *get_sphere_color(double intersectdist, t_ray *eye, t_sphere *sphere, t_ray *light_point, t_sphere *sphere_list)
{
	t_vector3 *hit_point;
	t_vector3 *sphere_normal;
	t_vector3 *hit_line;
	t_ray	*shadow_ray;

	if ((shadow_ray = malloc(sizeof(t_ray))) == NULL)
		return (0);

	//printf("sphere here is id: %d\n", sphere->id);

	hit_line = new_vector3(eye->dir->x * intersectdist,
	eye->dir->y * intersectdist, eye->dir->z * intersectdist);
	hit_point = add_vector3(eye->pos, hit_line, 0);
	sphere_normal = sub_vector3(hit_point, sphere->pos, 0);
	normalize(sphere_normal);

	double shadow_intersect;

	t_vector3 *light_p_dist = sub_vector3(light_point->pos, hit_point, 0);
	double mag = sqrt(pow(light_p_dist->x, 2) + pow(light_p_dist->y, 2) + pow(light_p_dist->z, 2));
	t_vector3 *object_color = new_vector3(0, 200, 200);

	object_color->x *= light_point->brightness / (4 * M_PI * pow(mag, 2));
	object_color->y *= light_point->brightness / (4 * M_PI * pow(mag, 2));
	object_color->z *= light_point->brightness / (4 * M_PI * pow(mag, 2));

	normalize(light_p_dist);


	double facing_ratio = scal_vector3(sphere_normal, light_p_dist, 0);
	facing_ratio *= 0.7; // can be edited with light intensity, need to ad K of specular

	double specular = 0;
	if(facing_ratio > 0.0001)
	{
		normalize(light_p_dist);
		t_vector3 *r = reflect(light_p_dist, sphere_normal);
		normalize(r);
		t_vector3 *v = new_vector3(-eye->dir->x,
			-eye->dir->y, -eye->dir->z);
		specular = pow(scal_vector3(r, v, 0), 400);
	}

	//printf("before %f %f %f\n", intersectdist, object_color->y, object_color->z);
	object_color->x = ft_constrain(facing_ratio * object_color->x + specular * 100, 0, 255);
	object_color->y = ft_constrain(facing_ratio * object_color->y + specular * 100, 0, 255);
	object_color->z = ft_constrain(facing_ratio * object_color->z + specular * 100, 0, 255);

	shadow_ray->pos = hit_point;
	shadow_ray->dir = light_p_dist;
	while(sphere_list)
	{
		if(sphere->id != sphere_list->id)
		{
			double shadow_intersect = intersect(shadow_ray, sphere_list);
			if(shadow_intersect)
			{
				object_color->x *= 0.1;
				object_color->y *= 0.1;
				object_color->z *= 0.1;
			}
		}
		sphere_list = sphere_list->next;

	}
	//printf("after %f %f %f\n", object_color->x, object_color->y, object_color->z);

	return (object_color);
}


t_vector2 *check_sphere_intersections(t_ray *eye, t_sphere *sphere_list)
{
	double t;
	double dist;
	t_sphere *sphere_hit;

	t = 0;
	dist = 0;
	sphere_hit = NULL;
	while(sphere_list)
	{
		dist = intersect(eye, sphere_list);
		if(dist > 1)
		{
			if(t == 0)
			{
				t = dist;
				sphere_hit = sphere_list;
			}
			else if(dist < t)
			{
				sphere_hit = sphere_list;
				t = dist;
			}
		}
		sphere_list = sphere_list->next;
	}
	if(sphere_hit)
		return (new_vector2(t, sphere_hit->id));
	else
		return (NULL);
}

t_sphere *add_sphere(t_vector3 *pos, double radius, int id)
{
	t_sphere *sphere;

	if ((sphere = malloc(sizeof(t_sphere))) == NULL)
		return (0);
	sphere->pos = pos;
	sphere->radius = radius;
	sphere->id = id;
	sphere->next = NULL;
	return (sphere);
}

double intersect(t_ray *ray, t_sphere *sphere)
{
	double t0, t1;
	t_vector3 *L = sub_vector3(sphere->pos, ray->pos, 0);
	float tca = scal_vector3(L, ray->dir, 0);
	if (tca < 0)
		return (0);
	float d2 = scal_vector3(L, L, 0) - tca * tca;
	if (d2 > pow(sphere->radius, 2))
		return (0);
	float thc = sqrt(pow(sphere->radius, 2) - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if(t0 <= 0 && t1 <= 0)
		return (0);
	if (t0 < t1)
		return (t0);
	else
		return (t1);
}
