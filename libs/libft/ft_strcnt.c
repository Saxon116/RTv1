/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 15:20:50 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/17 15:32:51 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcnt(char *src, char *listofchar)
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
			if (src[i] == listofchar[j])
				break ;
			if (src[i] != listofchar[j] && listofchar[j + 1] == '\0')
				return (0);
			++j;
		}
		++i;
	}
	return (1);
}
