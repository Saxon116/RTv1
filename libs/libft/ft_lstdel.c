/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:53:52 by lucmarti          #+#    #+#             */
/*   Updated: 2018/11/14 18:41:22 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nlst;

	if (alst != NULL)
		while (*alst != NULL)
		{
			nlst = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = nlst;
		}
	alst = NULL;
}
