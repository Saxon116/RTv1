/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 11:07:25 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/21 11:32:10 by lucmarti         ###   ########.fr       */
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

char			**ft_strarray(char **ar)
{
	char	**cpy;
	size_t	i;
	size_t	j;

	i = array_length(ar);
	if (!(cpy = malloc(sizeof(char **) * (i + 1))))
		return (NULL);
	cpy[i] = NULL;
	j = 0;
	while (j < i)
	{
		cpy[j] = ft_strdup(ar[j]);
		++j;
	}
	return (cpy);
}
