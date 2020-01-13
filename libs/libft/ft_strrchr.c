/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:10:45 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:43:26 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*cs;

	cs = (char *)s;
	while (*cs != '\0')
		++cs;
	while (cs >= s)
	{
		if (*cs == c)
			return (cs);
		--cs;
	}
	return (NULL);
}
