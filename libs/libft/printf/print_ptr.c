/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:08:24 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/07 10:20:06 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_validity(t_stat *arg, char *out, int *len)
{
	int f;

	f = arg->pr == 0 && out[2] == '0' ? 1 : 0;
	arg->pr = (arg->pr == 0 || arg->pr == -1) ? -1 : arg->pr + 2;
	if (f)
	{
		out[2] = 0;
		*len = 2;
	}
	else if (arg->pr < *len && arg->adj)
		arg->pr = *len;
	else if (arg->pr < *len)
		arg->pr = -1;
}

void		print_ptr(t_stat *arg, t_trail *core, int len)
{
	char	*out;
	int		i;

	out = ft_cptr(arg, core->ap);
	arg->str = out;
	len = ft_strlen(out);
	i = 0;
	check_validity(arg, out, &len);
	print_trail(arg, core, &i, len);
	if (!arg->adj || arg->fs < len)
	{
		ft_putstr(out);
		core->printed += len;
	}
	ft_memdel((void **)&(arg->str));
	arg->str = NULL;
}
