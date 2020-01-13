/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:15:41 by lucmarti          #+#    #+#             */
/*   Updated: 2018/12/05 10:52:33 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree_all(t_list **alst)
{
	t_list *tmp;

	if (alst)
	{
		while (*alst)
		{
			if ((*alst)->content)
				free((*alst)->content);
			tmp = *alst;
			*alst = (*alst)->next;
			free(tmp);
		}
	}
}
