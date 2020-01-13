/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:50:25 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/13 11:54:08 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_talt(t_stat *arg, char *text, int *cur)
{
	if (text[*cur] == '#')
		arg->alt = 1;
	else if (is_type(text[*cur]))
		arg->fmt = text[*cur];
}

static void	set_za(t_stat *arg, char *text, int *cur)
{
	if (text[*cur] == '0')
		arg->zero = 1;
	else if (text[*cur] == '-')
		arg->adj = 1;
}

static void	set_form(t_stat *arg, char *text, int *cur)
{
	arg->form = (text[*cur] == ' ' && arg->form != 2) ? 1 : 2;
}

static void	set_fspr(t_stat *arg, char *text, int *cur)
{
	int value;

	if ((text[*cur] == '.' && text[*cur + 1] == '*') || text[*cur] == '*')
	{
		value = (long long int)va_arg(*(arg->ap), long long);
		if (value < 0 && text[*cur] != '.')
			arg->adj = 1;
		if (text[*cur] == '.' && value >= 0)
			arg->pr = value;
		else if (text[*cur] != '.')
			arg->fs = (value < 0 ? value * -1 : value);
		*cur += text[*cur] == '.' ? 1 : 0;
		return ;
	}
	else if (text[*cur] != '.')
		arg->fs = ft_atoi(text + *cur);
	else
	{
		arg->pr = ft_atoi(text + *cur + 1);
		++(*cur);
	}
	while (text[*cur] != '\0' && (text[*cur] >= '0' && text[*cur] <= '9'))
		++(*cur);
	--(*cur);
}

/*
**	0 : '#' || type | 1 : '0' || '-' | 2 : ' ' || '+'
**  3 : field size and precision | 4 : modifiers
*/

void		init_aptr(t_stat *arg)
{
	arg->parser[0] = set_talt;
	arg->parser[1] = set_za;
	arg->parser[2] = set_form;
	arg->parser[3] = set_fspr;
	arg->parser[4] = set_mod;
}
