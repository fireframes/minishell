/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/29 23:17:17 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	splits_count(char const *str, char delim, int *inquotes)
{
	size_t	splits;
	size_t	i;

	splits = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == delim && !inquotes[i])
		{
			i++;
			continue ;
		}
		splits++;
		while (str[i])
		{
			if (str[i] == delim && !inquotes[i])
				break ;
			i++;
		}
	}
	return (splits);
}

static int	pop_arr(char **split, const char *s, char c, int *inquotes)
{
	size_t	i;
	size_t	j;
	size_t	word;
	size_t	sub_len;

	i = 0;
	j = 0;
	word = 0;
	sub_len = 0;
	while (s[i])
	{
		while (s[i] == c && !inquotes[i])
			i++;
		while (s[i] && (s[i] != c || inquotes[i]))
		{
			sub_len++;
			i++;
			word = 1;
		}
		if (word)
		{
			split[j] = (char *) malloc(sizeof(char) * (sub_len + 1));
			if (!split[j])
				return (-1);
			ft_strlcpy(split[j], &s[i - sub_len], sub_len + 1);
			j++;
			word = 0;
			sub_len = 0;
		}
	}
	split[j] = NULL;
	return (0);
}

char	**split_v3(char const *s, char c, int *inquotes)
{
	char	**arr_of_str;
	size_t	nb_of_splits;

	nb_of_splits = splits_count(s, c, inquotes);
	arr_of_str = (char **)malloc(sizeof(char *) * (nb_of_splits + 1));
	if (arr_of_str == NULL)
		return (NULL);
	if (pop_arr(arr_of_str, s, c, inquotes) < 0)
	{
		free_arr_of_arr(arr_of_str);
		return (NULL);
	}
	if (nb_of_splits == 0)
		return (NULL);
	return (arr_of_str);
}
