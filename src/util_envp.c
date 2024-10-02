/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/02 14:41:29 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Creates a copy of the environment variable list.
* It allocates space for the copies using static arrays,
* ensuring that copied environment variables do not exceed predefined limits.
*/
t_env	*copy_envp(char **envp)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (i >= ENVVAR_MAX)
		{
			perror("envp: size of envp list exceeds maximum value");
			free(env);
			return (NULL);
		}
		ft_strlcpy(env->envp_arr[i], envp[i], ft_strlen(envp[i]) + 1);
		env->envp_arr[i][PATH_MAX - 1] = '\0';
		i++;
	}
	env->envp_arr[i][0] = '\0';
	env->ptr_arr = env->envp_arr;
	return (env);
}

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

void	print_sorted_envp(t_env *envp)
{
	int		i;
	int		count;
	char	**sorted_list;

	count = 0;
	while (envp->ptr_arr[count] != NULL)
		count++;
	sorted_list = malloc(sizeof(char *) * count);
	i = 0;
	while (envp->ptr_arr[i] != NULL)
	{
		sorted_list[i] = envp->ptr_arr[i];
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
bool	isvalid_arg(char *arg)
{
	(void) arg;
	return (true);
}

// bool	env_exists(char *arg, t_env *envp)
// {
// 	return (true);
// }
