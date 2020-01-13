/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 10:31:13 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/07 10:31:15 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_alt(t_stat *la, char **str)
{
	int	alt;

	alt = (str[0][0] == '0' && str[0][1] == '\0') ? 0 : 1;
	if (la->alt && la->fs != 0 && la->zero)
		la->fs = la->fs != 0 ? la->fs - 2 : 0;
	ft_addz(str, la, ft_strlen(*str), 1);
	if (la->alt && la->fmt == 'X' && alt)
		*str = ft_strjoinf("0X", *str);
	else if (la->alt && alt)
		*str = ft_strjoinf("0x", *str);
}

static void	ft_upcase(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'f')
			str[i] -= 32;
		++i;
	}
}

static void	get_arg(uintmax_t *nu, va_list ap, t_stat *la)
{
	if (ft_strcmp(la->mod, "hh") == 0)
		*nu = (unsigned char)va_arg(ap, int);
	else if (ft_strcmp(la->mod, "h") == 0)
		*nu = (unsigned short)va_arg(ap, int);
	else if (ft_strcmp(la->mod, "l") == 0)
		*nu = va_arg(ap, unsigned long);
	else if (ft_strcmp(la->mod, "ll") == 0)
		*nu = va_arg(ap, unsigned long long);
	else if (ft_strcmp(la->mod, "j") == 0)
		*nu = va_arg(ap, uintmax_t);
	else if (ft_strcmp(la->mod, "z") == 0)
		*nu = va_arg(ap, size_t);
	else
		*nu = va_arg(ap, unsigned int);
}

char		*ft_cunh(t_stat *la, va_list ap, int type)
{
	char		*out;
	uintmax_t	nu;

	out = NULL;
	get_arg(&nu, ap, la);
	if (!(out = ft_chex(NULL, nu, 1)))
		out = ft_strdup("(null)");
	if (type == 1)
		ft_upcase(out);
	if (out[0] == '0' && la->pr == 0)
		out[0] = 0;
	if (out[0] != 0)
		ft_alt(la, &out);
	return (out);
}
