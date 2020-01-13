/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:17:21 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:43:14 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *cdst;

	cdst = dst;
	while (len > 0)
	{
		if (*src == '\0')
			*cdst = '\0';
		else
		{
			*cdst = *src;
			++src;
		}
		++cdst;
		--len;
	}
	return (dst);
}
