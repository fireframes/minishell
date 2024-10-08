/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/08/28 15:14:10 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	strncmp_v2(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*unsigned_s1;
	unsigned char	*unsigned_s2;

	index = 0;
	unsigned_s1 = (unsigned char *)s1;
	unsigned_s2 = (unsigned char *)s2;
	while (index < n)
	{
		if (unsigned_s1[index] != unsigned_s2[index])
			return (unsigned_s1[index] - unsigned_s2[index]);
		else if (unsigned_s1[index] == 0 || unsigned_s2 == 0)
			return (unsigned_s1[index] - unsigned_s2[index]);
		else
			index++;
	}
	return (0);
}

size_t	strlen_v2(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*strnstr_v2(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	size_t	i_h;
	size_t	needle_len;

	if (haystack == NULL && len == 0)
		return (NULL);
	i_h = 0;
	h = (char *) haystack;
	if (needle[0] == '\0')
		return (h);
	needle_len = strlen_v2(needle);
	if (h == NULL)
		if (strncmp_v2((h + i_h), needle, needle_len) == 0)
			return (h + i_h);
	while (((i_h + needle_len) <= len) && (haystack[i_h] != '\0'))
	{
		if (strncmp_v2((h + i_h), needle, needle_len) == 0)
			return (h + i_h);
		i_h++;
	}
	return (NULL);
}

char	*strjoin_v2(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;

	s3 = (char *)malloc((strlen_v2(s1) + strlen_v2(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (i < strlen_v2(s1))
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < (strlen_v2(s1) + strlen_v2(s2)))
	{
		s3[i] = s2[i - strlen_v2(s1)];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
