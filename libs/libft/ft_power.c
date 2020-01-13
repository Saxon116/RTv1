/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 12:25:49 by lucmarti          #+#    #+#             */
/*   Updated: 2019/02/22 11:05:05 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long	ft_power(unsigned long long x, unsigned long long n)
{
	if (n == 1)
		return (x);
	else if (n == 0)
		return (1);
	else
		return (x * ft_power(x, n - 1));
}
