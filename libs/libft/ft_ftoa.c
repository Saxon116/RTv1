/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:32:33 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/14 09:38:45 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlength(long long c)
{
	int i;

	i = 0;
	if (c == 0)
		return (1);
	if ((unsigned long long)c == (unsigned long long)MIN_LONG)
	{
		i = 1;
		c = c / 10;
	}
	c *= c < 0 ? -1 : 1;
	while (c > 0)
	{
		++i;
		c = c / 10;
	}
	return (i);
}

static void	ft_rparta(char *str, long rpart, int *len)
{
	if (rpart == 0)
		str[(*len)--] = '0';
	else if (rpart < 0)
	{
		str[(*len)--] = ((rpart % 10) * -1) + '0';
		rpart = rpart / 10;
		str[0] = '-';
		rpart = ft_abs(rpart);
	}
	while (rpart > 0)
	{
		str[(*len)--] = (rpart % 10) + '0';
		rpart = rpart / 10;
	}
}

static void	ft_aux(char *str, int precision, long long ftorpart, int *len)
{
	int test;

	test = ft_getlength(ftorpart);
	if (ftorpart == 0)
		test--;
	if (ftorpart < 0)
		ftorpart = ft_abs(ftorpart);
	while (ftorpart > 0)
	{
		str[(*len)--] = (ftorpart % 10) + '0';
		ftorpart = ftorpart / 10;
	}
	while (test < (precision >= 10 ? 10 : precision % 10))
	{
		str[(*len)--] = '0';
		++test;
	}
}

static void	ft_fparta(char *str, long double n, int *len, int precision)
{
	long double	fpart;
	long long	ftorpart;
	int			last;

	fpart = (n - (long long)n);
	fpart *= ft_power(10, (precision >= 10 ? 10 : precision));
	if (precision > 10)
		ft_fparta(str, fpart, len, precision - 10);
	if (precision <= 10)
	{
		fpart *= 10;
		ftorpart = (long long)fpart;
		ftorpart *= ftorpart < 0. ? -1 : 1;
		last = ftorpart % 10;
		ftorpart /= 10;
		if (last >= 5)
			ftorpart += 1;
	}
	else
		ftorpart = (long long)fpart;
	ft_aux(str, precision, ftorpart, len);
}

/*
**	If pr (precision) is superior to 0 we add 1 to the length (the precision
**	dot) then we later add pr to len + 1 to have the full string length.
**	Pr representing the number of digit after de precision dot.
*/

char		*ft_ftoa(long double n, int pr, int neg)
{
	char		*str;
	int			len;

	len = ft_getlength((long long)n);
	len += (n < 0. || neg ? 1 : 0);
	len += (pr > 0 ? 1 : 0);
	if (!(str = (char *)ft_memalloc(sizeof(char) * (len + pr + 1))))
		return (NULL);
	len = len + pr;
	str[len--] = '\0';
	if (pr > 0)
	{
		ft_fparta(str, n, &len, pr);
		str[len--] = '.';
	}
	ft_rparta(str, (long long)n, &len);
	if ((long long)n == 0 && (n < 0 || neg))
		str[0] = '-';
	return (str);
}
