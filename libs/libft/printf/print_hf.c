/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:54:02 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/13 11:43:41 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_ftrail(t_stat *arg, t_trail *core, int *i, int len)
{
	while (*i < arg->fs - len)
	{
		if (*i == 0 && arg->adj)
		{
			ft_putstr(arg->str);
			core->printed += len;
		}
		if (arg->zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		++(*i);
		++(core->printed);
	}
}

void		print_x(t_stat *arg, t_trail *core, int len, int type)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_cunh(arg, core->ap, type);
	len = ft_strlen(out);
	if (arg->pr != -1 && arg->pr < len)
		arg->pr = len;
	arg->str = out;
	print_ftrail(arg, core, &i, len);
	if (!arg->adj || arg->fs <= len)
	{
		ft_putstr(out);
		core->printed += len;
	}
	ft_memdel((void **)&(out));
	arg->str = NULL;
}

void		print_flt(t_stat *arg, t_trail *core, int len)
{
	char	*out;
	int		i;

	i = 0;
	out = ft_cflt(arg, core->ap);
	len = ft_strlen(out);
	arg->str = out;
	print_ftrail(arg, core, &i, len);
	if (!arg->adj || arg->fs <= len)
	{
		ft_putstr(out);
		core->printed += len;
	}
	ft_memdel((void **)&(out));
	arg->str = NULL;
}
