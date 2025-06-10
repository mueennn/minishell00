/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:43:17 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/10 14:01:34 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*node;

	if (!f || !lst)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		node = malloc(sizeof(t_list));
		if (!node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		node->content = f(lst->content);
		node->next = NULL;
		ft_lstadd_back(&new_lst, node);
		lst = lst->next;
	}
	return (new_lst);
}
