/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:16:19 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/16 13:33:57 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_checkneedle(char *haystack, char const *needle, size_t len)
{
	char	*cneedle;

	cneedle = (char *)needle;
	while (*haystack != '\0')
	{
		if (*cneedle == '\0')
			return (1);
		if (*haystack != *cneedle || (len == 0 && *cneedle != '\0'))
			return (0);
		++haystack;
		++cneedle;
		--len;
	}
	if (*haystack == *cneedle)
		return (1);
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hay;

	if (*needle == '\0' || !needle)
		return ((char *)haystack);
	while (*haystack != '\0' && len > 0)
	{
		if (*haystack == *needle)
		{
			hay = (char *)haystack;
			if (ft_checkneedle(hay, needle, len))
				return (hay);
		}
		++haystack;
		--len;
	}
	return (NULL);
}
