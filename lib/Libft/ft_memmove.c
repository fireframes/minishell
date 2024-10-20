/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:17:18 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/19 18:42:04 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_tmp;
	const unsigned char	*src_tmp;

	if (dest == NULL || src == NULL)
		return (dest);
	dest_tmp = dest;
	src_tmp = src;
	if (dest_tmp < src_tmp)
	{
		while (n--)
			*dest_tmp++ = *src_tmp++;
	}
	else
	{
		dest_tmp += n;
		src_tmp += n;
		while (n--)
			*--dest_tmp = *--src_tmp;
	}
	return (dest);
}
