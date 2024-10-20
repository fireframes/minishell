/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:28:58 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/19 14:42:07 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void	*s_tmp;

	s_tmp = s;
	while (n--)
	{
		*(unsigned char *)s_tmp = (unsigned char) c;
		s_tmp++;
	}
	return (s);
}
