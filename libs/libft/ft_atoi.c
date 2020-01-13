/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:50:23 by lucmarti          #+#    #+#             */
/*   Updated: 2019/04/15 10:25:50 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoi(const char *str)
{
	int			sign;
	int			nd;
	long long	ret;

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
	return (sign ? 0 - ret : ret);
}
