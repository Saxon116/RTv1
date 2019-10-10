/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:40:50 by nkellum           #+#    #+#             */
/*   Updated: 2019/10/10 10:43:06 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray *add_light(t_vector3 *pos, int brightness, int id)
{
	t_ray *light;

	if ((light = malloc(sizeof(t_ray))) == NULL)
		return (0);
	light->pos = pos;
	light->brightness = brightness;
	light->id = id;
	light->next = NULL;
	return (light);
}
