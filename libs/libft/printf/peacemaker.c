/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   peacemaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 15:28:18 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/13 11:46:48 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			set_priorities(t_stat *arg)
{
	if (arg->pr != -1 && is_integer(arg->fmt) && arg->zero)
		arg->zero = 0;
	if ((arg->zero && arg->adj) || (arg->zero && arg->fmt == 'p'))
		arg->zero = 0;
	if ((arg->fmt == 'i' || arg->fmt == 'd') && arg->alt)
		arg->alt = 0;
	if (arg->fmt == '%')
		arg->pr = -1;
	else if ((arg->fmt == 'f' || arg->fmt == 'F') && arg->pr == -1)
		arg->pr = 6;
}
