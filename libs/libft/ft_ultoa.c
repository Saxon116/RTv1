/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:42:32 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/09 15:04:02 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlength(uintmax_t c)
{
	int	i;

	if (c == 0)
		return (1);
	i = 0;
	while (c > 0)
	{
		++i;
		c = c / 10;
	}
	return (i);
}

char		*ft_ultoa(uintmax_t n)
{
	char	*str;
	int		len;

	len = ft_getlength(n);
	if (!(str = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	--len;
	str[len] = '0';
	while (n > 0)
	{
		str[len--] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
