/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:53:54 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/06 12:26:25 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_oct(t_stat *arg, t_trail *core, int len)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_coct(arg, core->ap);
	len = ft_strlen(out);
	arg->str = out;
	if (out[0] == '0' && arg->pr == 0 && !arg->alt)
		out[out[0] == '0' ? 0 : 1] = '\0';
	print_trail(arg, core, &i, out[0] == 0 ? 0 : len);
	if (!arg->adj || arg->fs <= len)
	{
		ft_putstr(out);
		core->printed += out[0] == 0 ? 0 : len;
	}
	ft_memdel((void **)&(arg->str));
	arg->str = NULL;
}

void	print_uint(t_stat *arg, t_trail *core, int len)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_cund(arg, core->ap);
	if (ft_strchr(out, '-'))
		arg->pr += arg->pr == -1 ? 0 : 1;
	len = ft_strlen(out);
	arg->str = out;
	if ((out[0] == '0' || out[1] == '0') && (arg->pr == 0 || arg->pr == 1))
		out[out[0] == '0' ? 0 : 1] = '\0';
	print_trail(arg, core, &i, out[0] == 0 ? 0 : len);
	if (!arg->adj || arg->fs <= len)
	{
		ft_putstr(out);
		core->printed += out[0] == 0 ? 0 : len;
	}
	ft_memdel((void **)&(arg->str));
	arg->str = NULL;
}

void	print_int(t_stat *arg, t_trail *core, int len)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_cint(arg, core->ap);
	if (ft_strchr(out, '-'))
		arg->pr += arg->pr == -1 ? 0 : 1;
	len = ft_strlen(out);
	arg->str = out;
	if ((out[0] == '0' || out[1] == '0') && (arg->pr == 0 || arg->pr == 1))
		out[out[0] == '0' ? 0 : 1] = '\0';
	print_trail(arg, core, &i, out[0] == '\0' ? 0 : len);
	if (!arg->adj || arg->fs <= len)
	{
		ft_putstr(out);
		core->printed += out[0] == 0 ? 0 : len;
	}
	ft_memdel((void **)&(arg->str));
	arg->str = NULL;
}

void	print_per(t_stat *arg, t_trail *core, int len)
{
	char	*out;
	int		i;

	i = 0;
	out = "%";
	len = ft_strlen(out);
	arg->str = out;
	print_trail(arg, core, &i, len);
	if (!arg->adj || arg->fs <= len)
	{
		ft_putstr(out);
		core->printed += len;
	}
}
