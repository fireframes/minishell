/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/01 17:46:53 by mmaksimo         ###   ########.fr       */
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

void	print_sorted_envp(char **envp)
{
	int		i;
	int		count;
	char	**sorted_list;

	count = 0;
	while (envp[count] != NULL)
		count++;
	sorted_list = malloc(sizeof(char *) * count);
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
		printf("declare -x ");
		printf("%s\n", sorted_list[i]);
		i++;
	}
	free(sorted_list);
}

// PROBLEM:	why this line is in envp list?
// 			"_=/home/mmaksimo/42/home_minishell/./minishell"
// TODO: 1) check args validity
// 		 2) update envp list
int	ft_export(t_cmd *cmd, char **envp)
{
	if (!cmd->args[1])
	{
		print_sorted_envp(envp);
		return (0);
	}
	return (0);
}
