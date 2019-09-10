/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/09/10 13:52:01 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	main(int argc, char **argv)
{
	t_vector3	*vec;

	vec = new_vector3(10, 10, 10);
	double prod = scal_vector3(vec, new_vector3(2, 2, 2), 0);
	printf("x = %f y = %f z = %f dot prod = %f\n",
	vec->x, vec->y, vec->z, prod);
}
