/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:31:21 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/14 09:37:50 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_arg(long double *nu, va_list ap, t_stat *la)
{
	if (ft_strcmp(la->mod, "l") == 0)
		*nu = (long double)(va_arg(ap, double));
	else if (ft_strcmp(la->mod, "ll") == 0)
		*nu = (long double)(va_arg(ap, long double));
	else
		*nu = (long double)(va_arg(ap, double));
}

char		*ft_cflt(t_stat *la, va_list ap)
{
	char				*out;
	long double			nu;
	int					neg;

	out = NULL;
	nu = -1;
	neg = 0;
	get_arg(&nu, ap, la);
	if (1 / nu < 0)
		neg = 1;
	if (!(out = ft_ftoa(nu, la->pr, neg)))
		out = ft_strdup("(null)");
	if (nu >= 0. && la->form != 0 && !neg)
		out = ft_strjoinf(la->form == 2 ? "+" : " ", out);
	if (out[0] == '0' && la->pr == 0)
		out[0] = 0;
	return (out);
}
