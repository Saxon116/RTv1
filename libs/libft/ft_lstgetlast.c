/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:14:59 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/29 10:15:40 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetlast(t_list **alst)
{
	t_list	*elem;

	if (alst)
		if (*alst)
		{
			elem = *alst;
			while (elem->next)
				elem = elem->next;
		}
	return (elem);
}
