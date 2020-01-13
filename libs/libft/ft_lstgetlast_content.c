/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetlast_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:15:55 by lucmarti          #+#    #+#             */
/*   Updated: 2019/05/29 10:17:11 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstgetlast_content(t_list **alst)
{
	t_list	*elem;

	if (alst)
		if (*alst)
		{
			elem = ft_lstgetlast(alst);
			return (elem->content);
		}
	return (NULL);
}
