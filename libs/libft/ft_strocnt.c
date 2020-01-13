/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strocnt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:26:48 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/21 10:36:43 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strocnt(char *src, char *listofchar)
{
	size_t	i;
	size_t	j;

	if (!src || !listofchar)
		return (src == NULL ? 0 : 1);
	i = 0;
	while (src[i])
	{
		j = 0;
		while (listofchar[j])
		{
			if (src[i] != listofchar[j] && listofchar[j + 1] == '\0')
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}
