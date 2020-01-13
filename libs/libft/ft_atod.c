/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 09:38:21 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/23 10:29:01 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	get_decimal(const char *str)
{
	int			nd;
	long double ret;

	nd = 0;
	ret = 0;
	++str;
	while (*str >= 48 && *str <= 57)
	{
		++nd;
		ret += (((double)(*str - 48)) / ft_power(10, nd));
		++str;
	}
	return (ret);
}

long double			ft_atod(const char *str)
{
	int			sign;
	int			nd;
	long double	ret;

	sign = 0;
	ret = 0;
	nd = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		++str;
	sign = *str == '-' ? 1 : 0;
	if (*str == '-' || *str == '+')
		++str;
	while (*str >= 48 && *str <= 57)
	{
		++nd;
		ret *= 10;
		ret += (*str - 48);
		++str;
		if ((ret > 9223372036854775807 || ret < 0) && nd >= 18)
			return (sign == 0 ? -1 : 0);
	}
	if (*str == '.')
		ret += get_decimal(str);
	return (sign ? 0 - ret : ret);
}
