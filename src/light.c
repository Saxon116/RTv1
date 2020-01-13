/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:06:21 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/07 12:24:44 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	reflect(t_vector3 *light, t_vector3 *normal, t_vector3 *ret)
{
	float dotprod;

	dotprod = 2 * vector3_scal(normal, light);
	normal->x *= dotprod;
	normal->y *= dotprod;
	normal->z *= dotprod;
	vector3_sub(normal, light, ret);
}

/*
**	vec -> [0] : normal, [1] : hit, [2] : eye dir
*/

static void	set_opt(double *fr, double *spec, t_vector3 *vec[3]
		, struct s_obj *obj)
{
	t_vector3	test;
	t_vector3	opt[2];

	*spec = 0;
	test.x = vec[0]->x;
	test.y = vec[0]->y;
	test.z = vec[0]->z;
	normalize_vector(&test);
	*fr = vector3_scal(&test, vec[1]);
	*fr = *fr > 1 ? 1 : *fr;
	*fr = *fr < 0. ? 0. : *fr;
	if (*fr > 0.0001 && obj->type != PLANE)
	{
		reflect(vec[1], vec[0], &opt[0]);
		normalize_vector(&(opt[0]));
		ft_initvector3(&opt[1], -(vec[2]->x), -(vec[2]->y)
				, -(vec[2]->z));
		*spec = pow(vector3_scal(&opt[0], &opt[1]), 400);
	}
	if (obj->type == PLANE)
		*fr = 1;
}

static void	add_light(t_vector3 *color, t_vector3 *add)
{
	color->x += add->x;
	color->y += add->y;
	color->z += add->z;
}

void		compute_light(struct s_obj *obj, struct s_display *dp
		, t_vector3 *normal, t_vector3 *color)
{
	size_t			i;
	double			spec[2];
	struct s_obj	*light;
	t_vector3		hit;
	t_vector3		rgb;

	i = -1;
	while (dp->lights[++i])
	{
		light = dp->lights[i];
		vector3_sub(&light->org, &obj->hit, &hit);
		spec[0] = vector3_norm(&hit);
		rgb.x = obj->rgb.x * (light->bright / (4 * M_PI * pow(spec[0], 2)));
		rgb.y = obj->rgb.y * (light->bright / (4 * M_PI * pow(spec[0], 2)));
		rgb.z = obj->rgb.z * (light->bright / (4 * M_PI * pow(spec[0], 2)));
		normalize_vector(&hit);
		set_opt(&spec[0], &spec[1], (t_vector3 *[3]){normal, &hit, &dp->eye.dir}
				, obj);
		rgb.x = rgb.x * spec[0] + 100 * spec[1];
		rgb.y = rgb.y * spec[0] + 100 * spec[1];
		rgb.z = rgb.z * spec[0] + 100 * spec[1];
		compute_shadows((struct s_obj *[2]){obj, light}, &obj->hit, &rgb, dp);
		add_light(color, &rgb);
	}
}
