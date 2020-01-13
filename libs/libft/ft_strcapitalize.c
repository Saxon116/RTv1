/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:48:39 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/19 10:46:25 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	check_index(int pos, char *str, int *sow)
{
	if (*sow)
	{
		if (str[pos] >= 97 && str[pos] <= 122)
			str[pos] -= 32;
		*sow = 0;
	}
	else if (str[pos] >= 65 && str[pos] <= 90)
		str[pos] += 32;
}

char		*ft_strcapitalize(char *str)
{
	int		i;
	int		flag;

	flag = 1;
	i = 0;
	while (str[i] != '\0')
	{
		while (!((str[i] >= 97 && str[i] <= 122) || (str[i] >= 48
						&& str[i] <= 57) || (str[i] >= 65 && str[i] <= 90)))
		{
			i++;
			flag = 1;
		}
		check_index(i, str, &flag);
		++i;
	}
	return (str);
}
