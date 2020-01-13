/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_aux2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 11:15:20 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/30 10:38:04 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vector3_pow(t_vector3 *v, size_t pow)
{
	size_t		n;
	t_vector3	initial;

	initial = *v;
	n = 1;
	if (pow == 0)
	{
		v->x = 1;
		v->y = 1;
		v->z = 1;
	}
	while (n < pow)
	{
		v->x *= initial.x;
		v->y *= initial.y;
		v->y *= initial.z;
		++n;
	}
}
