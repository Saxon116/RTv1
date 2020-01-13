/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:06:33 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/21 12:08:00 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarray_free(char **ar)
{
	size_t	i;

	if (!ar)
		return ;
	i = 0;
	while (ar[i])
	{
		ft_memdel((void **)&(ar[i]));
		++i;
	}
	ft_memdel((void **)&ar);
}
