/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_others2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:24:06 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/05 15:24:09 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strdup_v2(const char *s1)
{
	char	*str_cpy;
	size_t	index;

	str_cpy = (char *)malloc((strlen_v2(s1) + 1) * sizeof(char));
	if (str_cpy == NULL)
		return (0);
	index = 0;
	while (index < (strlen_v2(s1) + 1))
	{
		str_cpy[index] = s1[index];
		index++;
	}
	return (str_cpy);
}

char	*substr_v2(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if ((s == 0) || (len == 0) || (start >= strlen_v2(s)))
		return (strdup_v2(""));
	if (len + start > strlen_v2(s))
		len = strlen_v2(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	if (start < strlen_v2(s))
	{
		while (i < len)
		{
			substr[i] = s[i + (size_t)start];
			i++;
		}
	}
	substr[i] = '\0';
	return (substr);
}
