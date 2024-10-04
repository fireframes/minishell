/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/04 12:51:01 by mmaksimo         ###   ########.fr       */
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
// QUESTION: the function is almost the same as copy_envp. maybe do it with one?
int	add_env(char *arg, char ***envp)
{
	char	**envp_old;
	char	**envp_new;
	int		i;

	envp_old = *envp;
	envp_new = malloc(sizeof(char **) * (get_env_count(envp_old) + 2));
	if (envp_new == NULL)
		return (-1);
	i = 0;
	while (envp_old[i] != NULL)
	{
		envp_new[i] = ft_strdup(envp_old[i]);
		if (envp_new[i] == NULL)
			return (-1);
		i++;
	}
	envp_new[i] = ft_strdup(arg);
	if (envp_new[i] == NULL)
		return (-1);
	envp_new[i + 1] = NULL;
	*envp = envp_new;
	free_arr_of_arr(envp_old);
	return (0);
}

bool	isvalid_arg(char *arg)
{
	(void) arg;
	return (true);
}

// PROBLEM:	why this line is in envp list?
// 			"_=/home/mmaksimo/42/home_minishell/./minishell"
// TODO: 1) check args validity
// 		 2) update envp list
int	ft_export(t_cmd *cmd, char ***envp)
{
	if (!cmd->args[1])
	{
		if (print_sorted_env(*envp) < 0)
			return (-1);
		else
			return (0);
	}
	int j = 1;
	while (cmd->args[j] != NULL)
	{
		if (!isvalid_arg(cmd->args[j]))
		{
			printf("export: not valid in this context: %s\n", cmd->args[j]);
			return (-1);
		}
		// if (env_exists(cmd->args[j], envp))
		// 	update_envp(cmd->args[j], envp);
		// else
		add_env(cmd->args[j], envp);
		j++;
	}
	return (0);
}
