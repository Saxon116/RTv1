/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 10:01:05 by lucmarti          #+#    #+#             */
/*   Updated: 2018/12/20 10:16:05 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_replace(t_list **lst, t_list *elem, int first)
{
	if (first)
	{
		ft_memdel((void **)&(*lst)->content);
		elem->next = (*lst)->next;
		ft_memdel((void **)lst);
		*lst = elem;
	}
	else
	{
		ft_memdel((void **)&(*lst)->next->content);
		elem->next = (*lst)->next->next;
		ft_memdel((void **)&((*lst)->next));
		(*lst)->next = elem;
	}
}

int			ft_lstreplace(t_list **alst, t_list *todel, t_list *nelem)
{
	t_list	*cur;

	cur = *alst;
	if (!(alst && *alst && todel && nelem))
		return (0);
	if (cur == todel)
	{
		ft_replace(&cur, nelem, 0);
		return (1);
	}
	while (cur->next != todel)
		cur = cur->next;
	if (cur)
		ft_replace(&cur, nelem, 1);
	return (1);
}
