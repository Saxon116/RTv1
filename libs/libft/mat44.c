/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat44.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:15:51 by lucmarti          #+#    #+#             */
/*   Updated: 2019/09/24 16:13:34 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	mat44_init(double val[4][4], struct s_mat44 *matrix, int rx)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			matrix->x[i][j] = val[i][j];
			if (rx)
				matrix->rx[i][j] = 0;
			++j;
		}
		++i;
	}
}
