/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 01:48:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/27 20:30:53 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new_head;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	node = lst;
	new_node = ft_lstnew((*f)(node->content));
	new_head = new_node;
	(*del)(node->content);
	node = node->next;

	// free(node);
	while (node != NULL)
	{
		// if ((*f)(node->content) != NULL)
		new_node = ft_lstnew((*f)(node->content));
		ft_lstadd_back(&new_head, new_node);
		(*del)(node->content);
		node = node->next;

		// free(node);
	}
	return (new_head);
}
