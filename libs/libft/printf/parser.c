/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:19:06 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/13 10:52:34 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	arg_init(t_stat *arg)
{
	arg->flags = 0;
	arg->alt = 0;
	arg->adj = 0;
	arg->form = 0;
	arg->zero = 0;
	arg->fs = 0;
	arg->pr = -1;
	arg->fmt = 0;
	arg->mod = NULL;
	arg->str = NULL;
	init_aptr(arg);
}

void		set_mod(t_stat *arg, char *text, int *cur)
{
	int i;

	i = *cur;
	while (text[i] != '\0' && is_mod(text[i]))
		++i;
	*cur += (i - 1 - *cur);
	--i;
	while (i >= 0)
	{
		if (!is_mod(text[i]) || arg->mod)
			break ;
		if (text[i] == 'l' && (text[i - 1] == 'l' || text[i - 1] != 'l'))
			arg->mod = text[i - 1] == 'l' ? "ll" : "l";
		else if (text[i] == 'h' && (text[i - 1] == 'h' || text[i - 1] != 'h'))
			arg->mod = text[i - 1] == 'h' ? "hh" : "h";
		else if (text[i] == 'L' || text[i] == 'j')
			arg->mod = (text[i] == 'L' ? "L" : "j");
		else if (text[i] == 'z')
			arg->mod = "z";
		if (text[i - 1] == 'z' || text[i - 1] == 'j')
			arg->mod = text[i - 1] == 'j' ? "j" : "z";
		--i;
	}
	return ;
}

static int	arg_test(char text)
{
	size_t	i;
	char	*codex;

	codex = "#0- +*123456789.Llhjz";
	if (is_type(text))
		return (0);
	i = 0;
	while (codex[i] != '\0')
	{
		if (codex[i] == text)
		{
			if (i <= 2)
				return (i == 0 ? 0 : 1);
			if (i > 2 && i <= 4)
				return (2);
			if (i > 4 && i <= 15)
				return (3);
			if (i > 15 && i <= 20)
				return (4);
		}
		++i;
	}
	return (-1);
}

static void	arg_set(t_stat *arg, char *text, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		arg->parser[arg_test(text[i])](arg, text, &i);
		++i;
	}
}

/*
**	parse_arg : function that will read part of the text till the conversion
**		type flag (from % to %/i/c/p/s/f/d/o/u/x/X) and will retrieve the
**		correct parameters (flags, field width, precision, type, modifier).
*/

int			parse_arg(char *text, t_trail *core)
{
	int		i;
	t_stat	arg;

	i = 1;
	arg_init(&arg);
	arg.ap = &(core->ap);
	while (text[i] != '\0' && !is_type(text[i]))
	{
		if (is_unknown(text[i]))
			return (i);
		++i;
	}
	if (text[i] == '\0')
		return (i);
	arg_set(&arg, text, text[i] == '\0' ? i : i + 1);
	set_priorities(&arg);
	print_start(&arg, core);
	return (text[i] == '\0' ? i : i + 1);
}
