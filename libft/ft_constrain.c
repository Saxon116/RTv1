/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_constrain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:25:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/09/30 19:09:17 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_constrain(double val, double min, double max)
{
	if (val >= max)
		return (max);
	if (val <= min)
		return (min);
	return (val);
}
