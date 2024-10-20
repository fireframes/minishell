/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:15:34 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/23 12:41:57 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest0;

	dest0 = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	join_len;

	join_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = (char *)malloc(join_len * sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strlcat(joined, s2, join_len);
	return (joined);
}
