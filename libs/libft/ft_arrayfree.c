/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:04:00 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/18 16:05:36 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrayfree(char **ar)
{
	size_t	i;

	if (!ar)
		return (0);
	i = 0;
	while (ar[i])
	{
		ft_memdel((void **)&(ar[i]));
		++i;
	}
	ft_memdel((void **)&ar);
	return (1);
}
