/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/10/10 19:30:36 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_vector(t_vector3 *vec)
{
	printf("x = %f y = %f z = %f\n", vec->x, vec->y, vec->z);
}

int	main(int argc, char **argv)
{
	t_ray	*eye;
	t_ray	*light_list;
	t_ray	*light_list_head;
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



	light_list = add_light(new_vector3(10, 10, 0), 2000, 0);
	light_list_head = light_list;
	light_list->next = add_light(new_vector3(15, 10, 0), 2000, 1);
	light_list->next->next = add_light(new_vector3(20, 10, 0), 2000, 1);


	sphere_list = add_sphere(new_vector3(5, -1, -10), 3.0, 0);
	sphere_list_head = sphere_list;

	// sphere_list->next = add_sphere(new_vector3(5, 5, -20), 5.0, 1);
	// sphere_list->next->next = add_sphere(new_vector3(-5, 5, -20), 5.0, 2);

	plane_list = add_plane(new_vector3(0, -10, 0), new_vector3(0, 1, 0), 0);
	plane_list_head = plane_list;
	//plane_list->next = add_plane(new_vector3(0, 0, -50), new_vector3(0, 0, 1), 1);

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
				light_list = light_list_head;
				while(plane_list && plane_list->id != closest_plane->y)
					plane_list = plane_list->next;
				t_vector3 *color = new_vector3(0,0,0);
				while(light_list)
				{
					t_vector3 *current = get_plane_color(closest_plane->x, eye, plane_list, light_list, sphere_list_head);
					color->x += current->x;
					color->y += current->y;
					color->z += current->z;
					//add_vector3(color, current, 0);
					light_list = light_list->next;
				}
				//print_vector(color);

				color->x = ft_constrain(color->x, 0, 255);
				color->y = ft_constrain(color->y, 0, 255);
				color->z = ft_constrain(color->z, 0, 255);
				plot(i, j, mlx, color);
			}

			if(closest_sphere)
			{
				sphere_list = sphere_list_head;
				light_list = light_list_head;
				while(sphere_list && sphere_list->id != closest_sphere->y)
					sphere_list = sphere_list->next;
				t_vector3 *color = new_vector3(0,0,0);
				while(light_list)
				{
					//add_vector3(color, get_sphere_color(closest_sphere->x, eye, sphere_list, light_list, sphere_list), 0);
					t_vector3 *current = get_sphere_color(closest_sphere->x, eye, sphere_list, light_list, sphere_list_head);
					color->x += current->x;
					color->y += current->y;
					color->z += current->z;
					light_list = light_list->next;
				}
				color->x = ft_constrain(color->x, 0, 255);
				color->y = ft_constrain(color->y, 0, 255);
				color->z = ft_constrain(color->z, 0, 255);
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
