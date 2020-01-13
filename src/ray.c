/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:59:28 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/10 14:00:25 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			get_dst(struct s_display *dp, struct s_obj *obj)
{
	t_vector3	hitpoint;
	double		dst;

	vector3_sub(&(obj->hit), &(dp->eye.org), &hitpoint);
	dst = sqrt(hitpoint.x * hitpoint.x + hitpoint.y * hitpoint.y
			+ hitpoint.z * hitpoint.z);
	return (dst);
}

struct s_obj	*get_min_dist(struct s_display *dp, t_vector3 screen
		, double *dst)
{
	struct s_obj	*min_obj;
	double			min_dst;
	double			cpt_dst;
	int				i;

	vector3_sub(&screen, &(dp->eye.org), &(dp->eye.dir));
	normalize_vector(&(dp->eye.dir));
	i = 0;
	cpt_dst = -1;
	min_dst = INFINITY;
	while (dp->objs[i])
	{
		if (dp->objs[i]->intersection(&(dp->eye), dp->objs[i]))
			if ((cpt_dst = get_dst(dp, dp->objs[i])) > 0.0 && cpt_dst < min_dst)
			{
				min_dst = cpt_dst;
				min_obj = dp->objs[i];
			}
		++i;
	}
	*dst = min_dst;
	if (min_dst <= 0.0 || min_dst >= INFINITY)
		return (NULL);
	return (min_obj);
}

void			compute_viewdata(struct s_display *dp, double ratio
		, double scale)
{
	double			dst;
	t_vector3		screen;
	struct s_obj	*obj;
	size_t			xy[2];
	double			txy[2];

	xy[1] = 0;
	while (xy[1] < HEIGHT)
	{
		xy[0] = 0;
		while (xy[0] < WIDTH)
		{
			txy[0] = (2 * ((xy[0] + 0.5) / (double)WIDTH) - 1)
				* ratio * scale;
			txy[1] = (1 - 2 * ((xy[1] + 0.5) / (double)HEIGHT)) * scale;
			ft_initvector3(&screen, txy[0], txy[1], -(1 * VIEWDIST));
			rotate_xyz(&screen, &dp->crt);
			vector3_add(&screen, &dp->eye.org, &screen);
			if ((obj = get_min_dist(dp, screen, &dst)) && dst > 0.0)
				obj->render(dp, obj, xy[0], xy[1]);
			xy[0]++;
		}
		xy[1]++;
	}
}

void			render(struct s_display *dp)
{
	double aspect_ratio;
	double scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan(FOV / 2 * M_PI / 180);
	compute_viewdata(dp, aspect_ratio, scale);
}
