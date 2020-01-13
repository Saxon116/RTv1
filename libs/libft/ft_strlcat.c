/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:36:32 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:42:56 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*d;
	char	*s;
	size_t	vsize;
	size_t	len;

	d = dst;
	s = (char *)src;
	vsize = size;
	while (vsize-- != 0 && *d != '\0')
		++d;
	len = d - dst;
	vsize = size - len;
	if (vsize == 0)
		return (len + ft_strlen(src));
	while (*s != '\0')
	{
		if (vsize > 1)
		{
			*d++ = *s;
			--vsize;
		}
		++s;
	}
	*d = '\0';
	return (len + (s - src));
}
