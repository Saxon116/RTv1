/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 10:43:19 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/13 11:35:47 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_trail(t_stat *arg, t_trail *core, int *i, int len)
{
	while (*i < arg->fs - (arg->pr != -1 && !is_integer(arg->fmt) ? arg->pr
				: len))
	{
		if (*i == 0 && arg->adj)
		{
			if (is_integer(arg->fmt))
				ft_putstr(arg->str);
			else
				ft_putstrn(arg->str, (arg->pr != -1 ? arg->pr : len));
			core->printed += (arg->pr != -1 && !is_integer(arg->fmt) ? arg->pr
					: len);
		}
		if (arg->zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		++(*i);
		++(core->printed);
	}
}

void	print_str(t_stat *arg, t_trail *core, int len, int i)
{
	char	*out;
	int		null;

	null = 0;
	out = ft_cstr(arg, core->ap);
	if (out == NULL && (null = !null) == 1)
		out = ft_strdup("(null)");
	arg->str = out;
	len = ft_strlen(out);
	i = 0;
	arg->pr = arg->pr > len ? len : arg->pr;
	print_trail(arg, core, &i, len);
	if (!arg->adj || arg->fs < len)
	{
		ft_putstrn(out, (arg->pr != -1 ? arg->pr : len));
		core->printed += (arg->pr != -1 ? arg->pr : len);
	}
	if (null == 1)
		ft_memdel((void **)&out);
	arg->str = NULL;
}

void	print_char(t_stat *arg, t_trail *core)
{
	char	*out;
	int		i;

	out = ft_cchr(core->ap);
	i = 0;
	while (i < arg->fs - 1)
	{
		if (i == 0 && arg->adj)
		{
			ft_putchar(*out);
			core->printed += 1;
		}
		if (arg->zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		++i;
		++(core->printed);
	}
	if (!arg->adj)
	{
		ft_putchar(*out);
		core->printed += 1;
	}
	ft_memdel((void **)&out);
}

void	print_start(t_stat *arg, t_trail *core)
{
	if (arg->fmt == 'c')
		print_char(arg, core);
	else if (arg->fmt == 's' || arg->fmt == 'S')
		print_str(arg, core, 0, 0);
	else if (arg->fmt == 'p')
		print_ptr(arg, core, 0);
	else if (arg->fmt == 'i' || arg->fmt == 'd' || arg->fmt == 'D')
		print_int(arg, core, 0);
	else if (arg->fmt == 'u' || arg->fmt == 'U')
		print_uint(arg, core, 0);
	else if (arg->fmt == 'x' || arg->fmt == 'X')
		print_x(arg, core, 0, arg->fmt == 'x' ? 0 : 1);
	else if (arg->fmt == 'o' || arg->fmt == 'O')
		print_oct(arg, core, 0);
	else if (arg->fmt == '%')
		print_per(arg, core, 0);
	else if (arg->fmt == 'f' || arg->fmt == 'F')
		print_flt(arg, core, 0);
}
