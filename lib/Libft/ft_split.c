/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:50:02 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/29 03:08:18 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static void	pop_arr(char **split, const char *s, char c, size_t i)
{
	size_t	j;
	size_t	word;
	size_t	sub_len;

	j = 0;
	word = 1;
	sub_len = 0;
	while (s[i])
	{
		if (s[i] == c || s[i+1] == '\0')
		{
			if (word)
			{
				split[j] = (char*) malloc(sizeof(char) * (sub_len + 1));
				ft_strlcpy(split[j], &s[i - sub_len], sub_len + 1);
				j++;
				word = 0;
				sub_len = 0;
			}
		}
		else
		{
			word = 1;
			sub_len++;
		}
		i++;
	}
	split[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	word_cnt = 0;
	// int 	is_word = 0;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (i == 0 || s[i - 1] == c)
				word_cnt++;
		}
		i++;
	}
	printf("WORD CNT: %zu\n", word_cnt);
	split = (char **) malloc(sizeof(char *) * (word_cnt + 1));
	if (split == NULL)// || s == NULL)
		return (NULL);
	pop_arr(split, s, c, 0);
	// free(s);
	return (split);
}
