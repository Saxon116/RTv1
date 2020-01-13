/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:35:33 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/06 11:38:03 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	null_intersection(struct s_ray *ray, struct s_obj *obj)
{
	(void)ray;
	(void)obj;
	return (0);
}

static void		null_render(void *dp_, struct s_obj *obj
		, size_t x, size_t y)
{
	(void)dp_;
	(void)obj;
	(void)x;
	(void)y;
	return ;
}

void			init_methods(struct s_obj *obj)
{
	obj->intersection = &null_intersection;
	if (obj->type == SPHERE)
		obj->intersection = &intersect_sphere;
	else if (obj->type == PLANE)
		obj->intersection = &intersect_plane;
	else if (obj->type == CYLINDER)
		obj->intersection = &intersect_cylinder;
	else if (obj->type == CONE)
		obj->intersection = &intersect_cone;
}

void			init_renders(struct s_obj *obj)
{
	obj->render = &null_render;
	if (obj->type == SPHERE)
		obj->render = &sphere_render;
	else if (obj->type == PLANE)
		obj->render = &plane_render;
	else if (obj->type == CYLINDER)
		obj->render = &cylinder_render;
	else if (obj->type == CONE)
		obj->render = &cone_render;
}

void			init_display(struct s_display *dp)
{
	dp->mlx = mlx_init();
	dp->mlx_win = mlx_new_window(dp->mlx, WIDTH, HEIGHT, "rtv1");
	ft_initvector3(&(dp->eye.org), 0, 0, -300);
	ft_initvector3(&(dp->eye.dir), 0, 0, 0);
	dp->img_ptr = mlx_new_image(dp->mlx, WIDTH, HEIGHT);
	dp->img_str = mlx_get_data_addr(dp->img_ptr, &(dp->bpp),
			&(dp->size_line), &(dp->endian));
}
