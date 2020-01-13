/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 11:16:19 by lucmarti          #+#    #+#             */
/*   Updated: 2019/10/08 13:41:46 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_obj(struct s_display *dp)
{
	size_t	i;

	i = 0;
	while (dp->objs[i])
		ft_memdel((void **)&(dp->objs[i++]));
	ft_memdel((void **)&(dp->objs));
	i = 0;
	while (dp->lights[i])
		ft_memdel((void **)&(dp->lights[i++]));
	ft_memdel((void **)&(dp->lights));
}
