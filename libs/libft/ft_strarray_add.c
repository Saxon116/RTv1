/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 11:55:00 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/21 12:10:31 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	array_length(char **ar)
{
	size_t	i;

	if (!ar || !(*ar))
		return (0);
	i = 0;
	while (ar && ar[i])
		++i;
	return (i);
}

char			**ft_strarray_add(char **ar, char *elem)
{
	char	**out;
	size_t	l;
	size_t	i;

	i = 0;
	l = array_length(ar);
	if (!(out = malloc(sizeof(char *) * (l + 2))))
		return (NULL);
	while (i < l)
	{
		out[i] = ft_strdup(ar[i]);
		++i;
	}
	out[l] = ft_strdup(elem);
	out[l + 1] = NULL;
	ft_strarray_free(ar);
	return (out);
}
