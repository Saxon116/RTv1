/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_csp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:13:05 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/07 10:02:49 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_cchr(va_list ap)
{
	char	ch;
	char	*dstr;

	if (!(dstr = malloc(sizeof(char) * 2)))
		dstr = ft_strdup("(null)");
	else
	{
		ch = va_arg(ap, int);
		dstr[0] = ch;
		dstr[1] = '\0';
	}
	return (dstr);
}

char	*ft_cptr(t_stat *arg, va_list ap)
{
	char	*out;
	char	*tmp;
	void	*ptr;
	int		len;

	ptr = va_arg(ap, void *);
	if (!(out = ft_chex(ptr, 0, 0)))
		out = ft_strdup("(null)");
	else
	{
		len = ft_strlen(out);
		while (len < arg->pr)
		{
			out = ft_strjoinf("0", out);
			len++;
		}
		tmp = out;
		out = ft_strjoin("0x", out);
		ft_memdel((void **)&tmp);
	}
	return (out);
}

char	*ft_cstr(t_stat *arg, va_list ap)
{
	(void)arg;
	return (va_arg(ap, char *));
}
