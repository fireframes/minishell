/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/08/28 15:14:10 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	splits_count(char const *s, char c)
{
	size_t	splits;
	size_t	index;

	splits = 0;
	index = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		if (s[index] != '\0')
		{
			splits++;
			while (s[index] != c && s[index] != '\0')
				index++;
		}
	}
	return (splits);
}

static char	*cpy_n_go_nxt_splt(char **curr_substr, char *curr_s_pos, char c)
{
	size_t	curr_split_size;
	size_t	index;

	while (*curr_s_pos == c)
		curr_s_pos++;
	curr_split_size = 0;
	while (curr_s_pos[curr_split_size] && curr_s_pos[curr_split_size] != c)
		curr_split_size++;
	*curr_substr = (char *)malloc(sizeof(char) * (curr_split_size + 1));
	if (*curr_substr == NULL)
		return (NULL);
	index = 0;
	while (index < curr_split_size)
	{
		(*curr_substr)[index] = curr_s_pos[index];
		index++;
	}
	(*curr_substr)[index] = '\0';
	curr_s_pos = curr_s_pos + (curr_split_size + 1);
	return (curr_s_pos);
}

static void	fr_str_arr_n_subs(char ***ptr_to_arr_of_str, size_t strs_filled)
{
	size_t	index;

	index = 0;
	while (index < strs_filled)
	{
		free ((*ptr_to_arr_of_str)[index]);
		index++;
	}
	free (*ptr_to_arr_of_str);
	*ptr_to_arr_of_str = NULL;
}

char	**split_v2(char const *s, char c)
{
	char	**arr_of_str;
	size_t	index;
	size_t	nb_of_splits;

	nb_of_splits = splits_count(s, c);
	arr_of_str = (char **)malloc(sizeof(char *) * (nb_of_splits + 1));
	if (arr_of_str == NULL)
		return (NULL);
	arr_of_str[nb_of_splits] = NULL;
	index = 0;
	while (index < nb_of_splits)
	{
		s = cpy_n_go_nxt_splt(arr_of_str + index, (char *)s, c);
		if (s == NULL)
		{
			fr_str_arr_n_subs(&arr_of_str, index);
			return (NULL);
		}
		index++;
	}
	return (arr_of_str);
}
