/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:31:00 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/19 12:49:39 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	void	*s1_tmp;
	void	*s2_tmp;

	s1_tmp = (void *) s1;
	s2_tmp = (void *) s2;
	while (n--)
	{
		if (*(unsigned char *)s1_tmp != *(unsigned char *)s2_tmp)
			return (*(unsigned char *)s1_tmp - *(unsigned char *)s2_tmp);
		s1_tmp++;
		s2_tmp++;
	}
	return (0);
}
