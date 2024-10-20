/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:49:12 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/26 20:11:48 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *node;

	node = *lst;
	if (node == NULL)
		return ;
	ft_lstclear(&(node->next), del);
	(*del)(node->content);
	free(node);
	*lst = NULL;
}

// DO WITH WHILE LOOP AND WRITE TESTS!