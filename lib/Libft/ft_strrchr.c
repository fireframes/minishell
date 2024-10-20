/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:21:33 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/19 15:21:24 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_tmp;
	char	*s_last;
	int		found;

	if (s == NULL)
		return (NULL);
	s_tmp = (char *) s;
	found = 0;
	while (*s_tmp)
	{
		if (*s_tmp == (unsigned char) c)
		{
			s_last = s_tmp;
			found++;
		}
		s_tmp++;
	}
	if (found)
		return (s_last);
	else if (*s_tmp == (unsigned char) c)
		return (s_tmp);
	else
		return (NULL);
}
