/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 10:18:09 by lucmarti          #+#    #+#             */
/*   Updated: 2018/12/05 11:02:49 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_head(t_list **head)
{
	t_list *tmp;

	tmp = *head;
	*head = (*head)->next;
	if (tmp->content)
		free(tmp->content);
	free(tmp);
}

void		ft_lstfree_at(t_list **alst, size_t index)
{
	t_list *prev;
	t_list *cur;
	t_list *nxt;

	if (alst)
	{
		cur = *alst;
		prev = cur;
		if (*alst && index == 0)
			free_head(alst);
		while (cur && index + 1 > 1)
		{
			nxt = cur->next;
			if (index == 0)
			{
				prev->next = nxt;
				if (cur->content)
					free(cur->content);
				free(cur);
			}
			else
				prev = cur;
			cur = nxt;
		}
	}
}
