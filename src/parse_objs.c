/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:41:07 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/10 11:15:36 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Camera = 2 Components :
**		position && forward vector
*/

int		parse_camera(char *line, struct s_display *dp)
{
	char	**components;

	components = ft_strsplit(line, ' ');
	if (ft_arraylength(components) != 2 && ft_arrayfree(components))
		return (0);
	if ((!get_vector(&(dp->eye.org), components[0]) ||
				!get_vector(&(dp->crt), components[1]))
			&& ft_arrayfree(components))
		return (0);
	ft_initvector3(&dp->cdr, 0, 0, -1);
	ft_arrayfree(components);
	rotate_xyz(&dp->cdr, &dp->crt);
	return (1);
}

/*
**	Light = 2 Components :
**		position && brightness
*/

int		parse_light(char *line, struct s_display *dp)
{
	struct s_obj	*light;
	char			**components;

	if (!(light = obj_create()))
		return (0);
	components = ft_strsplit(line, ' ');
	if (ft_arraylength(components) != 2 && ft_arrayfree(components))
		return (0);
	light->type = 1;
	if ((!get_vector(&(light->org), components[0])))
	{
		ft_memdel((void **)&light);
		ft_arrayfree(components);
		return (0);
	}
	light->bright = ft_atoi(components[1]);
	ft_arrayfree(components);
	push_obj(light, dp);
	return (1);
}

/*
**	Sphere = 3 Components :
**		position && color && radius
*/

int		parse_sphere(char *line, struct s_display *dp)
{
	struct s_obj	*sphere;
	char			**components;

	if (!(sphere = obj_create()))
		return (0);
	components = ft_strsplit(line, ' ');
	if (ft_arraylength(components) != 4 && ft_arrayfree(components))
		return (0);
	sphere->type = 2;
	if ((!get_vector(&(sphere->org), components[0]))
			|| (!get_vector(&(sphere->rot), components[1]))
			|| (!get_vector(&(sphere->rgb), components[2])))
	{
		ft_memdel((void **)&sphere);
		ft_arrayfree(components);
		return (0);
	}
	sphere->dim[2] = ft_atoi(components[3]);
	ft_arrayfree(components);
	push_obj(sphere, dp);
	return (1);
}

/*
**	Plan =  Components :
**		position && color && radius
*/

int		parse_plane(char *line, struct s_display *dp)
{
	struct s_obj	*plane;
	char			**components;

	if (!(plane = obj_create()))
		return (0);
	components = ft_strsplit(line, ' ');
	if (ft_arraylength(components) != 4 && ft_arrayfree(components))
		return (0);
	plane->type = 3;
	if ((!get_vector(&(plane->org), components[0]))
			|| (!get_vector(&(plane->rot), components[1]))
			|| (!get_vector(&(plane->dir), components[2]))
			|| (!get_vector(&(plane->rgb), components[3])))
	{
		ft_memdel((void **)&plane);
		ft_arrayfree(components);
		return (0);
	}
	normalize_vector(&(plane->dir));
	ft_arrayfree(components);
	push_obj(plane, dp);
	return (1);
}
