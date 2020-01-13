/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:56:50 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:44:00 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getdim(char const *s, char c)
{
	while (*s != '\0')
	{
		if (*s != c)
		{
			while (*s != c && *s != '\0')
				++s;
			return (1 + ft_getdim(s, c));
		}
		++s;
	}
	return (0);
}

static int	ft_getlength(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s != '\0' && *s != c)
	{
		++s;
		++i;
	}
	return (i);
}

static int	ft_getsplit(char const *s, char c, char **tab, int j)
{
	int		i;
	size_t	splitlength;

	i = 0;
	splitlength = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			splitlength = ft_getlength(s, c);
			if (!(tab[i] = (char *)malloc(sizeof(char) * (splitlength + 1))))
				return (0);
			j = 0;
			while (*s != c && *s != '\0')
			{
				tab[i][j] = *s;
				++s;
				++j;
			}
			tab[i++][splitlength] = '\0';
		}
		else
			++s;
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	splitlength;

	if (!s)
		return (NULL);
	splitlength = ft_getdim(s, c);
	if (!(tab = (char **)malloc(sizeof(char*) * (splitlength + 1))))
		return (NULL);
	tab[splitlength] = 0;
	return (ft_getsplit(s, c, tab, 0) ? tab : NULL);
}
