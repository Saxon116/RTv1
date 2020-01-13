/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:27:41 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:44:27 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checktrim(char const *s, int index, size_t dir)
{
	size_t	mod;
	size_t	count;
	size_t	len;

	mod = dir == 1 ? 1 : -1;
	count = 0;
	len = ft_strlen(s);
	while ((index >= 0 && (size_t)index <= len) && ((s[index] == ' ')
			|| (s[index] == '\n') || (s[index] == '\t')))
	{
		index += mod;
		++count;
	}
	return (count);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	len -= (ft_checktrim(s, 0, 1) + ft_checktrim(s, len - 1, 0));
	len = ((int)len < 0 ? 0 : len);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		++s;
	str[len] = '\0';
	i = 0;
	while (*s != '\0' && len > 0)
	{
		--len;
		str[i++] = *s;
		++s;
	}
	return (str);
}
