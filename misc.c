/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:33:41 by nkellum           #+#    #+#             */
/*   Updated: 2019/11/07 14:20:41 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_texture *load_texture(t_mlx *mlx, char *filename, int width, int height)
{
	t_texture *texture;

	if ((texture = malloc(sizeof(t_texture))) == NULL)
		return (0);
	texture->img_texture_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, filename, &width, &height);
	texture->img_texture_str = mlx_get_data_addr(texture->img_texture_ptr, &(mlx->bpp),
	&(mlx->size_line), &(mlx->endian));
	return (texture);
}

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
