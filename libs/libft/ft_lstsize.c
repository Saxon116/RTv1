/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 09:57:32 by lucmarti          #+#    #+#             */
/*   Updated: 2018/12/20 09:59:47 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize(t_list **alst)
{
	size_t	count;
	t_list	*cur;

	count = 0;
	if (!alst)
		if (!(*alst))
			return (count);
	cur = *alst;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}
