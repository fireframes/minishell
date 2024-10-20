/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:28:51 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/25 18:57:00 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_map;
	unsigned int	len_s;
	unsigned int	i;

	len_s = ft_strlen(s);
	s_map = (char *) malloc((len_s + 1) * sizeof(char));
	if (s_map == NULL)
		return (NULL);
	i = 0;
	while (i < len_s)
	{
		s_map[i] = (*f)(i, s[i]);
		i++;
	}
	s_map[i] = '\0';
	return (s_map);
}
