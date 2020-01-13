/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:46:03 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/06 15:37:57 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		ft_ocount(uintmax_t n, int base)
{
	size_t c;

	c = (n == 0 ? 1 : 0);
	while (n > 0)
	{
		++c;
		n = n / base;
	}
	return (c);
}

static size_t		ft_hcount(uintmax_t n, int base)
{
	size_t c;

	c = (n == 0 ? 1 : 0);
	while (n > 0)
	{
		++c;
		n = n / base;
	}
	return (c);
}

char				*ft_chex(void *ptr, uintmax_t n, int t)
{
	char			*out;
	size_t			len;
	uintmax_t		lptr;
	uintmax_t		res;

	lptr = t == 0 ? (long unsigned)ptr : n;
	len = ft_hcount(lptr, 16);
	if (!(out = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	out[len] = '\0';
	out[0] = '0';
	len--;
	res = 0;
	while (lptr > 0)
	{
		res = lptr % 16;
		lptr = lptr / 16;
		if (res < 10)
			out[len] = res + '0';
		else
			out[len] = (res - 10) + 'a';
		--len;
	}
	return (out);
}

char				*ft_coct_aux(uintmax_t n)
{
	char			*out;
	size_t			len;
	uintmax_t		res;

	len = ft_ocount(n, 8);
	if (!(out = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	out[len] = '\0';
	len--;
	res = 0;
	if (n == 0)
		out[0] = '0';
	while (n > 0)
	{
		res = n % 8;
		n = n / 8;
		if (res < 8)
			out[len] = res + '0';
		--len;
	}
	return (out);
}
