/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:31:00 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/19 12:48:39 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*s_tmp;

	s_tmp = (void *) s;
	while (n--)
	{
		if (*(unsigned char *)s_tmp == (unsigned char) c)
			return (s_tmp);
		s_tmp++;
	}
	return (NULL);
}
