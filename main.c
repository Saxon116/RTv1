/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/09/16 15:32:10 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plot(int x, int y, t_mlx *mlx, double white)
{
	int index;

	index = 4 * (y * WIDTH) + 4 * x;
	// printf("white times 255 %d\n", (char)(white * 255.0));
	mlx->img_str[index] = (char)(white * 255.0);
	mlx->img_str[index + 1] = (char)(white * 255.0);
	mlx->img_str[index + 2] = (char)(white * 255.0);
}

void	initialize_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "RTv1");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->img_str = mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp),
	&(mlx->size_line), &(mlx->endian));
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
	if(x0 <= 0 && x1 <= 0)
		return (0);
    if (x0 < x1)
    	return (x0);
	else
		return (x1);
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
        double t0, t1; // solutions for t if the ray intersects
        // geometric solution
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
        // analytic solution
        // double a = scal_vector3(ray->dir, ray->dir, 0);
        // double b = 2 * scal_vector3(ray->dir, L, 0);
        // double c = scal_vector3(L, L, 0) - pow(sphere->radius, 2);
		// return (solveQuadratic(a, b, c));

		if(t0 <= 0 && t1 <= 0)
			return (0);
	    if (t0 < t1)
	    	return (t0);
		else
			return (t1);
}

int	main(int argc, char **argv)
{
	t_ray	*eye;
	t_vector3 *screen;
	t_vector3 *hit_point;
	t_vector3 *sphere_normal;
	t_vector3 *hit_line;
	t_sphere *sphere;
	t_mlx	*mlx;

	if ((mlx = malloc(sizeof(t_mlx))) == NULL)
		return (0);
	initialize_mlx(mlx);
	if ((eye = malloc(sizeof(t_ray))) == NULL)
		return (0);
	if ((sphere = malloc(sizeof(t_sphere))) == NULL)
		return (0);
	sphere->pos = new_vector3(0, 0 , -50);
	sphere->radius = 100.0;
	eye->pos = new_vector3(0, 0, -200);
	screen = new_vector3(-WIDTH / 2, -HEIGHT / 2, -100);


	// printf("%f %f %f\normalizing...\n", vec->x, vec->y, vec->z);
	// normalize(vec);
	// printf("%f %f %f\n", vec->x, vec->y, vec->z);
	int hitnum = 0;
	double intersectdist = 0.0;

	while(screen->y < HEIGHT/ 2)
	{
		screen->x = -WIDTH / 2;
		while(screen->x < WIDTH / 2)
		{
			eye->dir = sub_vector3(screen, eye->pos, 0);
			normalize(eye->dir);
			intersectdist = intersect(eye, sphere);
			if(intersectdist)
			{
				hit_line = new_vector3(eye->dir->x * intersectdist,
				eye->dir->y * intersectdist, eye->dir->y * intersectdist);
				hit_point = add_vector3(eye->pos, hit_line, 0);
				sphere_normal = sub_vector3(hit_point, sphere->pos, 0);
				normalize(sphere_normal);
				t_vector3 *view_normal = new_vector3(-eye->dir->x, -eye->dir->y,
				-eye->dir->z);
				double facing_ratio = scal_vector3(sphere_normal, view_normal, 0);
				if(facing_ratio > 0.0)
					plot(screen->x + WIDTH / 2, screen->y + HEIGHT/ 2, mlx, facing_ratio);
			}
			else
				plot(screen->x + WIDTH / 2, screen->y + HEIGHT/ 2, mlx, 0.3);
			screen->x++;
		}
		screen->y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, win_close, mlx);
	mlx_loop(mlx->mlx_ptr);

	return (0);
}
