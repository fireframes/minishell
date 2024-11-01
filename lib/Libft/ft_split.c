/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:50:02 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/01 20:36:03 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pop_arr(char **split, char *s_cpy, char const *s, size_t i)
{
	size_t	j;
	size_t	word_len;

	j = 0;
	word_len = 0;
	while (i <= ft_strlen(s))
	{
		if (s_cpy[i] == '\0' || i == ft_strlen(s))
		{
			if (word_len)
			{
				split[j] = ft_strdup(&s_cpy[i - word_len]);
				if (split[j] == NULL)
					return (0);
				j++;
				word_len = 0;
			}
		}
		else
			word_len++;
		i++;
	}
	split[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*s_cpy;
	size_t	i;
	size_t	word_cnt;

	s_cpy = ft_strdup(s);
	if (s_cpy == NULL || s == NULL)
		return (NULL);
	i = 0;
	word_cnt = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_cnt++;
		if (s[i] == c)
			s_cpy[i] = '\0';
		i++;
	}
	split = (char **) malloc(sizeof(char *) * (word_cnt + 1));
	if (split == NULL)
		return (NULL);
	if (!pop_arr(split, s_cpy, s, 0))
		return (NULL);
	free(s_cpy);
	return (split);
}
