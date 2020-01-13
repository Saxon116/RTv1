/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:10:28 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:42:03 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *copy_dst;
	unsigned char *copy_src;

	copy_dst = (unsigned char *)dst;
	copy_src = (unsigned char *)src;
	while (n > 0)
	{
		*copy_dst = *copy_src;
		++copy_dst;
		++copy_src;
		--n;
	}
	return (dst);
}
