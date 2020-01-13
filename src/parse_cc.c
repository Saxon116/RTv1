/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:44:27 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/07 16:01:10 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	cylinder = 3 Components :
**		position && rotation && dir && color && radius
*/

int		parse_cylinder(char *line, struct s_display *dp)
{
	struct s_obj	*cylinder;
	char			**components;

	if (!(cylinder = obj_create()))
		return (0);
	components = ft_strsplit(line, ' ');
	if (ft_arraylength(components) != 5 && ft_arrayfree(components))
		return (0);
	cylinder->type = 4;
	if ((!get_vector(&(cylinder->org), components[0]))
			|| (!get_vector(&(cylinder->rot), components[1]))
			|| (!get_vector(&(cylinder->dir), components[2]))
			|| (!get_vector(&(cylinder->rgb), components[3])))
	{
		ft_memdel((void **)&cylinder);
		ft_arrayfree(components);
		return (0);
	}
	normalize_vector(&(cylinder->dir));
	cylinder->dim[2] = ft_atoi(components[4]);
	ft_arrayfree(components);
	push_obj(cylinder, dp);
	return (1);
}

/*
**	cone = 5 Components :
**		position && rotation && dir && color && radius
*/

int		parse_cone(char *line, struct s_display *dp)
{
	struct s_obj	*cone;
	char			**components;

	if (!(cone = obj_create()))
		return (0);
	components = ft_strsplit(line, ' ');
	if (ft_arraylength(components) != 5 && ft_arrayfree(components))
		return (0);
	cone->type = 5;
	if ((!get_vector(&(cone->org), components[0]))
			|| (!get_vector(&(cone->rot), components[1]))
			|| (!get_vector(&(cone->dir), components[2]))
			|| (!get_vector(&(cone->rgb), components[3])))
	{
		ft_memdel((void **)&cone);
		ft_arrayfree(components);
		return (0);
	}
	normalize_vector(&(cone->dir));
	cone->dim[2] = ft_atoi(components[4]);
	ft_arrayfree(components);
	push_obj(cone, dp);
	return (1);
}
