/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:31:03 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/11 12:57:14 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"

# define HEIGHT 1000
# define WIDTH 1000
# define VIEWDIST 1
# define FOV 90

# define LRED "\x1b[31m"
# define LGRE "\x1b[32m"
# define LRES "\x1b[0m"

struct			s_parser
{
	t_list	*lines;
	int		size;
};

struct			s_ray
{
	t_vector3	org;
	t_vector3	dir;
};

/*
**	Objects types :
**	0 - camera
**	1 - light
**	2 - sphere
**	3 - plane
**	4 - cylinder
**	5 - cone
*/

# define CAM 0
# define LIGHT 1
# define SPHERE 2
# define PLANE 3
# define CYLINDER 4
# define CONE 5

struct			s_obj
{
	int			type;
	float		dim[3];
	t_vector3	org;
	t_vector3	rot;
	t_vector3	dir;
	t_vector3	rgb;
	t_vector3	hit;
	long		bright;
	double		(*intersection) (struct s_ray *ray, struct s_obj *obj);
	void		(*render) (void *dp, struct s_obj *obj
			, size_t x, size_t y);
};

struct			s_display
{
	void				*mlx;
	void				*mlx_win;
	void				*img_ptr;
	char				*img_str;
	int					bpp;
	int					size_line;
	int					endian;
	struct s_ray		eye;
	t_vector3			crt;
	t_vector3			cdr;
	int					obj_count;
	int					light_count;
	struct s_obj		**objs;
	struct s_obj		**lights;
};

/*
**	FILE : main.c
*/

/*
**	FILE : error.c
*/
void			error(char *msg);

/*
**	FILE : event.c
*/
int				key_handler(int keycode, void *param);
int				win_close(void *param);

/*
**	FILE : free.c
*/
void			free_obj(struct s_display *dp);

/*
**	FILE : init.c
*/
void			init_display(struct s_display *dp);
void			init_methods(struct s_obj *obj);
void			init_renders(struct s_obj *obj);

/*
**	FILE : intersect.c
*/
void			intersect(struct s_ray *ray, struct s_display *dp);

/*
**	FILE : obj.c
*/
struct s_obj	*obj_create(void);
void			push_obj(struct s_obj *obj, struct s_display *dp);

/*
**	FILE : math.c
*/
double			solve_quadratic(double a, double b, double c, double *ret);

/*
**	FILE : parser.c
*/
void			init_parser(char *file, struct s_display *dp);

/*
**	FILE : parse_objs.c
*/
int				parse_camera(char *line, struct s_display *dp);
int				parse_light(char *line, struct s_display *dp);
int				parse_sphere(char *line, struct s_display *dp);
int				parse_plane(char *line, struct s_display *dp);

/*
**	FILE : parse_cc.c
*/
int				parse_cylinder(char *line, struct s_display *dp);
int				parse_cone(char *line, struct s_display *dp);

/*
**	FILE : ray.c
*/
void			plot(int x, int y, struct s_display *dp
		, t_vector3 *color);
void			compute_shadows(struct s_obj *obj[2], t_vector3 *impact
		, t_vector3 *color, struct s_display *dp);
void			compute_light(struct s_obj *obj, struct s_display *dp
		, t_vector3 *normal, t_vector3 *color);
void			plane_render(void *dp_, struct s_obj *plane
		, size_t x, size_t y);
void			sphere_render(void *dp_, struct s_obj *sphere
		, size_t x, size_t y);
void			cylinder_render(void *dp_, struct s_obj *cylinder
		, size_t x, size_t y);
void			cone_render(void *dp_, struct s_obj *cone
		, size_t x, size_t y);
double			intersect_plane(struct s_ray *ray, struct s_obj *plane);
double			intersect_sphere(struct s_ray *ray, struct s_obj *sphere);
double			intersect_cylinder(struct s_ray *ray, struct s_obj *sphere);
double			intersect_cone(struct s_ray *ray, struct s_obj *sphere);
void			render(struct s_display *dp);

/*
**	FILE : rotation.c
*/
void			rotate_x(t_vector3 *org, double a);
void			rotate_y(t_vector3 *org, double a);
void			rotate_z(t_vector3 *org, double a);
void			rotate_xyz(t_vector3 *org, t_vector3 *rot);

/*
**	FILE : vector_tools.c
*/
double			vector3_norm(t_vector3 *v);
void			normalize_vector(t_vector3 *vec);
int				get_vector(t_vector3 *toset, char *input);
void			invert_vector(t_vector3 *toinvert);

#endif
