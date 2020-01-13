/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3cp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 10:55:09 by lucmarti          #+#    #+#             */
/*   Updated: 2019/01/08 10:58:45 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3	*vector3_copy(t_vector3 *src)
{
	t_vector3	*cp;

	if (!src || !(cp = new_vector3(src->x, src->y, src->z)))
		return (NULL);
	return (cp);
}
