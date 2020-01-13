/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:51:26 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/13 11:35:32 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_integer(char c)
{
	if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

int	is_type(char c)
{
	int		i;
	char	*codex;

	codex = "icpsfdouxXDOUSF%";
	i = 0;
	while (codex[i] != '\0')
		if (codex[i++] == c)
			return (1);
	return (0);
}

int	is_mod(char c)
{
	int		i;
	char	*codex;

	codex = "Lhjlz";
	i = 0;
	if (c < codex[0] || c > 'z')
		return (0);
	while (codex[i] != '\0')
	{
		if (c == codex[i])
			return (1);
		if (c < codex[i])
			return (0);
		++i;
	}
	return (0);
}

int	is_unknown(char c)
{
	int		i;
	char	*codex;

	codex = " 0#+-.cspLhjlzouxXDUOFfid%123456789*";
	i = 0;
	while (codex[i] != '\0')
	{
		if (c == codex[i])
			return (0);
		++i;
	}
	return (1);
}
