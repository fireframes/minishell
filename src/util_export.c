/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:01:04 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/04 13:01:40 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort(char **arr, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(char **envp)
{
	int		i;
	int		count;
	char	**sorted_list;

	count = 0;
	while (envp[count] != NULL)
		count++;
	sorted_list = malloc(sizeof(char *) * count);
	if (!sorted_list)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		sorted_list[i] = envp[i];
		i++;
	}
	bubble_sort(sorted_list, count);
	i = 0;
	while (i < count)
	{
		printf("declare -x %s\n", sorted_list[i]);
		i++;
	}
	free(sorted_list);
	return (0);
}
