/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_split2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/14 21:34:11 by mmaksimo         ###   ########.fr       */
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

static void	skip_delimiter(t_split_data *data)
{
	while (data->str[data->i] == data->delimiter && !data->inquotes[data->i])
		data->i++;
}

static int	allocate_and_copy(t_split_data *data, size_t len)
{
	data->split_array[data->words] = (char *)malloc(sizeof(char) * (len + 1));
	if (!data->split_array[data->words])
		return (-1);
	ft_strlcpy(data->split_array[data->words],
		&data->str[data->i - len], len + 1);
	data->words++;
	return (0);
}

static int	pop_arr(char **split, const char *s, char c, int *inquotes)
{
	size_t			sub_len;
	t_split_data	data;

	data.str = s;
	data.delimiter = c;
	data.inquotes = inquotes;
	data.i = 0;
	data.words = 0;
	data.split_array = split;
	while (data.str[data.i])
	{
		skip_delimiter(&data);
		sub_len = count_word_length(&data);
		if (sub_len > 0)
		{
			if (allocate_and_copy(&data, sub_len) == -1)
				return (-1);
		}
	}
	data.split_array[data.words] = NULL;
	return (0);
}

char	**split_v2(char const *s, char c, int *inquotes)
{
	char	**arr_of_str;
	size_t	nb_of_splits;

	nb_of_splits = splits_count(s, c, inquotes);
	if (nb_of_splits == 0)
		return (NULL);
	arr_of_str = (char **)malloc(sizeof(char *) * (nb_of_splits + 1));
	if (arr_of_str == NULL)
		return (NULL);
	if (pop_arr(arr_of_str, s, c, inquotes) < 0)
	{
		free_arr_of_arr(arr_of_str);
		return (NULL);
	}
	return (arr_of_str);
}
