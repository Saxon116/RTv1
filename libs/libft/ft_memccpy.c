/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:37:29 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:41:57 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	unsigned char	test;

	test = (unsigned char)c;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (n > 0)
	{
		*cdst = *csrc;
		if (*csrc == test)
		{
			++cdst;
			return (cdst);
		}
		++cdst;
		++csrc;
		--n;
	}
	return (NULL);
}
