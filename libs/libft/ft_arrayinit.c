/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 10:25:26 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/23 10:32:45 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	**ft_arrayinit(size_t size, void *default_)
{
	size_t	i;
	void	**array;

	if (!(array = malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		array[i] = default_;
		printf("%p\n", array[i]);
		++i;
	}
	return (array[i]);
}
