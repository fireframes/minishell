/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:26:01 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/23 14:22:35 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *) big);
	i = 0;
	j = 0;
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *) &big[i - j + 1]);
		}
		else
		{
			i -= j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
