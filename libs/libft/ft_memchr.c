/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:00:59 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:41:59 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *csrc;
	unsigned char test;

	test = (unsigned char)c;
	csrc = (unsigned char *)s;
	while (n > 0)
	{
		if (*csrc == test)
			return (csrc);
		--n;
		++csrc;
	}
	return (NULL);
}
