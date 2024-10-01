/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/01 20:50:37 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// PROBLEM:	why this line is in envp list?
// 			"_=/home/mmaksimo/42/home_minishell/./minishell"
// TODO: 1) check args validity
// 		 2) update envp list

// void	update_envp(char *arg, t_env *envp)
// {

// }

// void	add_envp(char *arg, t_env *envp)
// {
// 	int i;

// 	i = 0;
// 	while (i < ENVVAR_MAX)
// 	{
// 		if (envp->ptr_arr[i] == NULL)
// 		{
// 			ft_strlcpy(envp[i], arg, PATH_MAX);

// 			envp[i + 1] = NULL;

// 			return ;
// 		}
// 		i++;
// 	}
// }
int get_env_count(t_env *env)
{
    int i = 0;
    while (env->ptr_arr[i] != NULL && i < ENVVAR_MAX)
        i++;
    return i;
}

int add_envp(char *arg, t_env *env)
{
    int count = get_env_count(env);
    if (count >= ENVVAR_MAX - 1)
        return -1;  // No more room

    ft_strlcpy(env->envp_arr[count], arg, PATH_MAX);
    env->envp_arr[count][PATH_MAX - 1] = '\0';
    env->ptr_arr[count] = env->envp_arr[count];
    env->ptr_arr[count + 1] = NULL;
    return 0;
}

int	ft_export(t_cmd *cmd, t_env *envp)
{
	if (!cmd->args[1])
	{
		print_sorted_envp(envp);
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
		add_envp(cmd->args[j], envp);
		j++;
	}
	return (0);
}
