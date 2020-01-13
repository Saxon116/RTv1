/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:03:49 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/17 12:01:42 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfn(char **s1, char **s2, int n)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2 || !(*s1) || !(*s2))
		return (NULL);
	len = ft_strlen(*s1) + ft_strlen(*s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[0] = '\0';
	str = ft_strcat(str, *s1);
	str = ft_strcat(str, *s2);
	if (n == 1 || n == 3)
		ft_memdel((void **)s1);
	if (n == 2 || n == 3)
		ft_memdel((void **)s2);
	return (str);
}
