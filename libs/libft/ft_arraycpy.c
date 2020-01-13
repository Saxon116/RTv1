/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraycpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:07:41 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/21 10:18:37 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_delete(void **ar, size_t i)
{
	while (i > 0)
	{
		ft_memdel((void **)&(ar[i]));
		--i;
	}
	ft_memdel((void **)&(ar[i]));
	ft_memdel((void **)&(ar));
	return (NULL);
}

void	**ft_arraycpy(void **ar, size_t type_size, size_t ptr_size)
{
	void	**cpy;
	size_t	ar_len;
	size_t	index;

	if (!ptr_size || !type_size)
		return (NULL);
	ar_len = ft_arraylength((char **)ar);
	if (!(cpy = malloc(ptr_size * (ar_len + 1))))
		return (NULL);
	cpy[ar_len] = NULL;
	index = 0;
	while (index < ar_len)
	{
		if (!(cpy[index] = ft_memalloc(sizeof(ar[index]))))
			return (ft_delete(cpy, index));
		cpy[index] = ft_memcpy(cpy[index], ar[index], sizeof(ar[index]));
		++index;
	}
	return (cpy);
}
