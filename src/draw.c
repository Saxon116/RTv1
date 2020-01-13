/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:33:45 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/07 13:45:00 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_constrain(int val, int min, int max)
{
	if (val >= max)
		return (max);
	if (val <= min)
		return (min);
	return (val);
}

void		plot(int x, int y, struct s_display *mlx, t_vector3 *color)
{
	int	index;

	index = 4 * (y * WIDTH) + 4 * x;
	mlx->img_str[index] = (char)ft_constrain(color->z, 0, 255);
	mlx->img_str[index + 1] = (char)ft_constrain(color->y, 0, 255);
	mlx->img_str[index + 2] = (char)ft_constrain(color->x, 0, 255);
}
