/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:44:35 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/22 19:54:38 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*dest_tmp;

	if (dest == NULL || src == NULL)
		return (dest);
	dest_tmp = dest;
	while (n--)
		*((unsigned char *)dest_tmp++) = *((unsigned char *)src++);
	return (dest);
}
