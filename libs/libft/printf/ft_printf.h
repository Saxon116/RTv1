/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:02:25 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/24 10:06:26 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include "../../libft/libft.h"

typedef struct	s_trail
{
	va_list		ap;
	char		*ftext;
	int			printed;
}				t_trail;

/*
**	0	| 1		| 2	| 3 | 4 | 5 | 6 | 7 | 8
**	alt	  zero	  +   -  ' '
*/
typedef struct	s_stat
{
	short		flags;
	int			alt;
	int			adj;
	int			form;
	int			zero;
	int			fs;
	int			pr;
	char		fmt;
	char		*mod;
	char		*str;
	void		(*parser[6]) (struct s_stat *arg, char *text, int *cur);
	va_list		*ap;
}				t_stat;

/*
**	print_hf.c
*/
void			print_x(t_stat *arg, t_trail *core, int len, int type);
void			print_flt(t_stat *arg, t_trail *core, int len);

/*
**	print_int.c
*/
void			print_oct(t_stat *arg, t_trail *core, int len);
void			print_uint(t_stat *arg, t_trail *core, int len);
void			print_int(t_stat *arg, t_trail *core, int len);
void			print_per(t_stat *arg, t_trail *core, int len);

/*
**	print.c
*/
void			print_trail(t_stat *arg, t_trail *core, int *i, int len);
void			print_ptr(t_stat *arg, t_trail *core, int len);
void			print_str(t_stat *arg, t_trail *core, int len, int i);
void			print_char(t_stat *arg, t_trail *core);
void			print_start(t_stat *arg, t_trail *core);

/*
**	get_x.c
*/
char			*ft_cunh(t_stat *la, va_list ap, int type);

/*
**	get_f.c
*/
char			*ft_cflt(t_stat *la, va_list ap);

/*
**	get_iuo.c
*/
void			ft_addz(char **out, t_stat *arg, int len, long long nu);
char			*ft_cint(t_stat *arg, va_list ap);
char			*ft_coct(t_stat *la, va_list ap);
char			*ft_cund(t_stat *la, va_list ap);

/*
**	get_csp.c
*/
char			*ft_cchr(va_list ap);
char			*ft_cptr(t_stat *arg, va_list ap);
char			*ft_cstr(t_stat *arg, va_list ap);

/*
**	hex.c
*/
char			*ft_chex(void *ptr, uintmax_t n, int t);
char			*ft_coct_aux(uintmax_t n);

/*
**	init.c
*/
t_trail			*trail_init(char *text);
void			trail_free(t_trail *core);

/*
**	bool.c
*/
int				is_integer(char c);
int				is_type(char c);
int				is_mod(char c);
int				is_unknown(char c);

/*
**	peacemaker.c
*/
void			set_priorities(t_stat *arg);

/*
**	init.c
*/
void			init_aptr(t_stat *arg);

/*
**	parser.c
*/
void			set_mod(t_stat *arg, char *text, int *cur);
int				parse_arg(char *text, t_trail *core);

/*
**	ft_printf.c
*/
int				ft_printf(char *text, ...);

/*
**	error.c
*/
void			err_die(char *msg);

#endif
