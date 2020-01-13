/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:56:28 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/01 15:46:19 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;

	if (n == 0 || !src)
		return (NULL);
	dup = NULL;
	i = 0;
	if (!(dup = (char *)malloc(sizeof(*dup) * (n + 1))))
		return (NULL);
	dup[n] = '\0';
	while (*src != '\0' && i < n)
	{
		dup[i] = *src;
		++src;
		++i;
	}
	dup[i] = '\0';
	return (dup ? dup : NULL);
}
