/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:33:06 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/07 12:22:10 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

struct s_obj	*obj_create(void)
{
	struct s_obj	*obj;

	if (!(obj = malloc(sizeof(struct s_obj))))
		return (NULL);
	obj->type = -1;
	ft_initvector3(&(obj->org), 0, 0, 0);
	ft_initvector3(&(obj->rot), 0, 0, 0);
	ft_initvector3(&(obj->dir), 0, 0, 0);
	ft_initvector3(&(obj->rgb), 0, 0, 0);
	obj->bright = 0;
	obj->intersection = NULL;
	obj->dim[0] = 0;
	obj->dim[1] = 0;
	obj->dim[2] = 0;
	ft_initvector3(&(obj->hit), 0, 0, 0);
	return (obj);
}

void			push_obj(struct s_obj *obj, struct s_display *dp)
{
	int i;

	i = 0;
	rotate_xyz(&obj->dir, &obj->rot);
	if (obj->type == PLANE)
		invert_vector(&obj->dir);
	if (obj->type == LIGHT)
	{
		while (dp->lights && dp->lights[i])
			++i;
	}
	else
		while (dp->objs && dp->objs[i])
			++i;
	init_methods(obj);
	init_renders(obj);
	if (obj->type == LIGHT)
	{
		dp->lights[i] = obj;
		dp->light_count += 1;
	}
	else
		dp->objs[i] = obj;
}
