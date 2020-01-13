/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2cp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 10:55:09 by lucmarti          #+#    #+#             */
/*   Updated: 2019/01/08 10:58:57 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector2	*vector2_copy(t_vector2 *src)
{
	t_vector2	*cp;

	if (!src || !(cp = new_vector2(src->x, src->y)))
		return (NULL);
	return (cp);
}
