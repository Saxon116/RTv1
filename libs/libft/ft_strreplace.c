/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 16:51:16 by lucmarti          #+#    #+#             */
/*   Updated: 2019/06/13 01:59:21 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(const char *src, const char *toreplace,
		const char *replace)
{
	char	*output;
	char	*tmp;
	char	*target;

	output = NULL;
	if (!src || !toreplace || ft_strstr(src, toreplace) == NULL)
		return (NULL);
	if (!replace)
		output = ft_strnew(ft_strlen(src) - ft_strlen(toreplace) + 1);
	else
		output = ft_strnew(ft_strlen(src) - ft_strlen(toreplace)
				+ ft_strlen(replace) + 1);
	target = ft_strstr(src, toreplace);
	tmp = ft_strncat(output, src, target - src);
	if (replace)
		tmp = ft_strcat(output, replace);
	else
		tmp = output;
	output = ft_strcat(tmp, target + ft_strlen(toreplace));
	return (output);
}
