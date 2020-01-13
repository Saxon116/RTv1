/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:07:02 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/07 10:52:00 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	retvalue(double x0, double x1, double *ret)
{
	if (x0 <= 0 && x1 <= 0)
	{
		*ret = 0.0;
		return (0);
	}
	if (x0 < x1 && x0 > 0.0)
	{
		*ret = x0;
		return (x0);
	}
	else
	{
		*ret = x1;
		return (x1);
	}
}

double			solve_quadratic(double a, double b, double c, double *ret)
{
	double discr;
	double x0;
	double x1;
	double q;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		x1 = -0.5 * b / a;
		x0 = x1;
	}
	else
	{
		q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	return (retvalue(x0, x1, ret));
}
