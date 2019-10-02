/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/10/02 20:12:50 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plot(int x, int y, t_mlx *mlx, t_vector3 *color)
{
	int index;

	index = 4 * (y * WIDTH) + 4 * x;
	mlx->img_str[index] = (char)color->z;
	mlx->img_str[index + 1] = (char)color->y;
	mlx->img_str[index + 2] = (char)color->x;
}

void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "RTv1");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img_str = mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp),
	&(mlx->size_line), &(mlx->endian));
}

void	normalize(t_vector3 *vec)
{
	double mag;

	mag = sqrt(pow(vec->x, 2) + pow(vec->y, 2) + pow(vec->z, 2));
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
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

t_vector3 *reflect(t_vector3 *light, t_vector3 *normal)
{
		float dotprod = 2 * scal_vector3(normal, light, 0);
		normal->x *= dotprod;
		normal->y *= dotprod;
		normal->z *= dotprod;

		return sub_vector3(normal, light, 0);
}

double solveQuadratic(double a, double b, double c)
{
    double discr = b * b - 4 * a * c;
	double x0, x1;
    if (discr < 0)
		return (0);
    else if (discr == 0)
		x0 = x1 = - 0.5 * b / a;
    else {
        double q = (b > 0) ?
            -0.5 * (b + sqrt(discr)) :
            -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
	if(x0 <= 0.0 && x1 <= 0.0)
		return (0);
	if(x0 < 0)
		return (x1);
	if(x1 < 0)
		return (x0);
    if (x0 < x1)
    	return (x0);
	else
		return (x1);
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

double intersect_cone(t_ray *ray, t_cone *cone)
{
	double dv = scal_vector3(ray->dir, cone->dir, 0);
	double theta_rad = cone->theta * (M_PI/180);
	double a = pow(dv, 2) - pow(cos(theta_rad), 2);

	t_vector3 *co = sub_vector3(ray->pos, cone->pos, 0);
	t_vector3 *cos_theta = new_vector3(0, 0, 0);
	cos_theta->x = co->x * pow(cos(theta_rad), 2);
	cos_theta->y = co->y * pow(cos(theta_rad), 2);
	cos_theta->z = co->z * pow(cos(theta_rad), 2);
	double b = 2 * (dv * scal_vector3(co, cone->dir, 0) - scal_vector3(ray->dir, cos_theta, 0));
	double c = pow(scal_vector3(co, cone->dir, 0), 2) - scal_vector3(co, cos_theta, 0);

	return solveQuadratic(a, b, c);

}

double intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_vector3 *test = sub_vector3(ray->pos, cylinder->pos, 0);

	double a = pow(ray->dir->x , 2) + pow(ray->dir->y, 2);
	double b = 2 * test->x * ray->dir->x + 2 * test->y * ray->dir->y;
	double c = pow(test->x, 2) + pow(test->y, 2) - pow(cylinder->radius, 2);

	return solveQuadratic(a, b, c);
}

t_vector3 *get_plane_color(double t, t_ray *eye, t_ray *plane, t_ray *light_point, t_sphere *sphere_list)
{
	t_vector3 *hit_point;
	t_vector3 *hit_line;
	t_ray	*shadow_ray;

	if ((shadow_ray = malloc(sizeof(t_ray))) == NULL)
		return (0);
	int light_brightness = 10000;


	hit_line = new_vector3(eye->dir->x * t,
	eye->dir->y * t, eye->dir->z * t);
	hit_point = add_vector3(eye->pos, hit_line, 0);

	t_vector3 *light_p_dist = sub_vector3(light_point->pos, hit_point, 0);
	double mag = sqrt(pow(light_p_dist->x, 2) + pow(light_p_dist->y, 2) + pow(light_p_dist->z, 2));
	t_vector3 *object_color = new_vector3(200, 200, 200);

	object_color->x *= light_brightness / (4 * M_PI * pow(mag, 2));
	object_color->y *= light_brightness / (4 * M_PI * pow(mag, 2));
	object_color->z *= light_brightness / (4 * M_PI * pow(mag, 2));

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

t_vector3 *get_sphere_color(double intersectdist, t_ray *eye, t_sphere *sphere, t_ray *light_point, t_sphere *sphere_list)
{
	t_vector3 *hit_point;
	t_vector3 *sphere_normal;
	t_vector3 *hit_line;
	t_ray	*shadow_ray;

	if ((shadow_ray = malloc(sizeof(t_ray))) == NULL)
		return (0);

	//printf("sphere here is id: %d\n", sphere->id);
	int light_brightness = 10000;

	hit_line = new_vector3(eye->dir->x * intersectdist,
	eye->dir->y * intersectdist, eye->dir->z * intersectdist);
	hit_point = add_vector3(eye->pos, hit_line, 0);
	sphere_normal = sub_vector3(hit_point, sphere->pos, 0);
	normalize(sphere_normal);

	double shadow_intersect;

	t_vector3 *light_p_dist = sub_vector3(light_point->pos, hit_point, 0);
	double mag = sqrt(pow(light_p_dist->x, 2) + pow(light_p_dist->y, 2) + pow(light_p_dist->z, 2));
	t_vector3 *object_color = new_vector3(0, 200, 200);

	object_color->x *= light_brightness / (4 * M_PI * pow(mag, 2));
	object_color->y *= light_brightness / (4 * M_PI * pow(mag, 2));
	object_color->z *= light_brightness / (4 * M_PI * pow(mag, 2));

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
		double shadow_intersect = intersect(shadow_ray, sphere_list);
		if(shadow_intersect)
		{
			object_color->x *= 0.1;
			object_color->y *= 0.1;
			object_color->z *= 0.1;
		}
		sphere_list = sphere_list->next;
	}
	//printf("after %f %f %f\n", object_color->x, object_color->y, object_color->z);

	return (object_color);
}

int	main(int argc, char **argv)
{
	t_ray	*eye;
	t_ray	*light_point;
	t_vector3 *screen;
	t_sphere *sphere_list;
	t_sphere *sphere_list_head;
	t_ray	*plane_list;
	t_ray	*plane_list_head;
	t_mlx	*mlx;

	if ((mlx = malloc(sizeof(t_mlx))) == NULL)
		return (0);
	initialize_mlx(mlx);
	if ((eye = malloc(sizeof(t_ray))) == NULL)
		return (0);
	if ((light_point = malloc(sizeof(t_ray))) == NULL)
		return (0);


	light_point->pos = new_vector3(-15, 10, -10);

	sphere_list = add_sphere(new_vector3(0, -5, -20), 5.0, 0);
	sphere_list_head = sphere_list;

	sphere_list->next = add_sphere(new_vector3(5, 5, -20), 5.0, 1);
	sphere_list->next->next = add_sphere(new_vector3(-5, 5, -20), 5.0, 1);

	plane_list = add_plane(new_vector3(0, -10, 0), new_vector3(0, 1, 0), 0);
	plane_list_head = plane_list;
	plane_list->next = add_plane(new_vector3(0, 0, -50), new_vector3(0, 0, 1), 1);

	eye->pos = new_vector3(0, 0, 0);




	int hitnum = 0;
	double intersectdist = 0.0;
	double aspect_ratio = (double)WIDTH / (double)HEIGHT;
	double fov = 90.0;
	double scale = tan(fov / 2 * M_PI / 180);


	int i;
	int j = 0;
	while(j < HEIGHT)
	{
		i = 0;
		while(i < WIDTH)
		{
			double x = (2 * (i + 0.5) / (double)WIDTH - 1) * aspect_ratio * scale;
            double y = (1 - 2 * (j + 0.5) / (double)HEIGHT) * scale;
			screen = new_vector3(x, y, -1);
			eye->dir = sub_vector3(screen, eye->pos, 0);
			normalize(eye->dir);

			plane_list = plane_list_head;
			sphere_list = sphere_list_head;
			t_vector2 *closest_sphere = check_sphere_intersections(eye, sphere_list);
			t_vector2 *closest_plane = check_plane_intersections(eye, plane_list);


			if(closest_sphere && closest_plane)
			{
				if(closest_sphere->x < closest_plane->x)
					closest_plane = NULL;
				else
					closest_sphere = NULL;
			}




			if(closest_plane)
			{
				plane_list = plane_list_head;
				while(plane_list && plane_list->id != closest_plane->y)
					plane_list = plane_list->next;
				t_vector3 *color = get_plane_color(closest_plane->x, eye, plane_list, light_point, sphere_list);
				plot(i, j, mlx, color);
			}

			if(closest_sphere)
			{
				sphere_list = sphere_list_head;
				while(sphere_list && sphere_list->id != closest_sphere->y)
					sphere_list = sphere_list->next;
				t_vector3 *color = get_sphere_color(closest_sphere->x, eye, sphere_list, light_point, sphere_list);
				plot(i, j, mlx, color);
			}




			// if(t)
			// {
			// 	//plot(i, j, mlx, 1, 0,  new_vector3(255,255,255));
			// 	hit_line = new_vector3(eye->dir->x * t,
			// 	eye->dir->y * t, eye->dir->z * t);
			// 	hit_point = add_vector3(eye->pos, hit_line, 0);
			// 	//printf("%f %f %f\n", view_normal->x, view_normal->y, view_normal->z);
			// 	t_vector3 *light_p_dist = sub_vector3(light_point->pos, hit_point, 0);
			// 	double mag = sqrt(pow(light_p_dist->x, 2) + pow(light_p_dist->y, 2) + pow(light_p_dist->z, 2));
			// 	t_vector3 *object_color = new_vector3(200, 200, 200);
			//
			// 	object_color->x *= light_brightness / (4 * M_PI * pow(mag, 2));
			// 	object_color->y *= light_brightness / (4 * M_PI * pow(mag, 2));
			// 	object_color->z *= light_brightness / (4 * M_PI * pow(mag, 2));
			//
			// 	normalize(light_p_dist);
			// 	shadow_ray->pos = hit_point;
			// 	shadow_ray->dir = light_p_dist;
			//
			// 	double shadow_intersect = intersect(shadow_ray, sphere);
			// 	if(shadow_intersect)
			// 	{
			// 		object_color->x *= 0.5;
			// 		object_color->y *= 0.5;
			// 		object_color->z *= 0.5;
			// 	}
			//
			// 	plot(i, j, mlx, 1, 0,  object_color);
			// }

			i++;
		}
		j++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, win_close, mlx);
	mlx_loop(mlx->mlx_ptr);

	return (0);
}
