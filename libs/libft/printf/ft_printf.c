/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 10:01:41 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/09 12:41:04 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	print_ud (useless data) : Will print data until arg is found
*/

void	print_ud(t_trail *core, char *text, int cur)
{
	while (text[cur] != '\0')
	{
		if (text[cur] == '%')
			cur += parse_arg((text + cur), core);
		else
		{
			ft_putchar(text[cur]);
			core->printed += 1;
			++cur;
		}
	}
}

/*
**	ft_printf : Main function fo ft_printf, will start all the machinery.
*/

int		ft_printf(char *text, ...)
{
	int		ret;
	t_trail core;

	core.ftext = text;
	core.printed = 0;
	va_start(core.ap, text);
	print_ud(&core, text, 0);
	ret = core.printed;
	return (ret);
}
