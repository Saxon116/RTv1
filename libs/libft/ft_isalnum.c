/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:24:41 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/21 12:15:42 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigitx(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

static int	ft_isalphax(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int			ft_isalnum(int c)
{
	return (ft_isdigitx(c) || ft_isalphax(c));
}
