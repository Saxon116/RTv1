/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:30:35 by lucmarti          #+#    #+#             */
/*   Updated: 2019/11/06 11:23:30 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(int ac, char **av)
{
	struct s_display dp;

	if (ac > 2 || ac < 2)
	{
		ft_putendl_fd("usage : ./rtv1 [rtv1_scene_file]", 2);
		exit(1);
	}
	ft_printf("\x1b[33mRTV1 Log\x1b[0m\n");
	init_display(&dp);
	init_parser(av[1], &dp);
	render(&dp);
	ft_printf("\x1b[33mRTV1 calculated and rendered\x1b[0m\n");
	mlx_put_image_to_window(dp.mlx, dp.mlx_win, dp.img_ptr, 0, 0);
	mlx_hook(dp.mlx_win, 2, 0, key_handler, &dp);
	mlx_hook(dp.mlx_win, 17, 0, win_close, &dp);
	mlx_loop(dp.mlx);
	return (0);
}
