/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:31:29 by nkellum           #+#    #+#             */
/*   Updated: 2019/10/10 10:44:33 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 900

typedef struct		s_ray
{
	t_vector3		*pos;
	t_vector3		*dir;
	int				id;
	int				brightness;
	struct s_ray	*next;
}					t_ray;

typedef struct		s_sphere
{
	t_vector3		*pos;
	double			radius;
	int				id;
	struct s_sphere	*next;
}					t_sphere;

typedef struct	s_cone
{
	t_vector3	*pos;
	t_vector3	*dir;
	double		theta;
}				t_cone;

typedef struct	s_cylinder
{
	t_vector3	*pos;
	t_vector3	*dir;
	double		radius;
}				t_cylinder;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_str;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;


int				deal_key(int key, void *param);
int				win_close(void *param);
void			initialize_mlx(t_mlx *mlx);
double intersect_plane(t_ray *ray, t_ray *plane);
t_ray *add_plane(t_vector3 *pos, t_vector3 *dir, int id);
t_vector2 *check_plane_intersections(t_ray *eye, t_ray *plane_list);
t_vector3 *get_plane_color(double t, t_ray *eye, t_ray *plane, t_ray *light_point, t_sphere *sphere_list);
t_vector3 *get_sphere_color(double intersectdist, t_ray *eye, t_sphere *sphere, t_ray *light_point, t_sphere *sphere_list);
t_vector2 *check_sphere_intersections(t_ray *eye, t_sphere *sphere_list);
t_sphere *add_sphere(t_vector3 *pos, double radius, int id);
double intersect(t_ray *ray, t_sphere *sphere);
void	plot(int x, int y, t_mlx *mlx, t_vector3 *color);
void	initialize_mlx(t_mlx *mlx);
void	normalize(t_vector3 *vec);
t_vector3 *reflect(t_vector3 *light, t_vector3 *normal);
double solveQuadratic(double a, double b, double c);
t_ray *add_light(t_vector3 *pos, int brightness, int id);





#endif
