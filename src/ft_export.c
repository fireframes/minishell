/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/08 15:55:05 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. update path with totally new path
// 2. concatenate to old path
// 3. if empty == ""
static int	update_envp(char *arg, char **env_ptr)
{
	char	*new_env;
	char	*tmp;
	size_t	new_len;

	new_len = ft_strlen(arg) + 1;
	new_env = malloc(sizeof(char *) * new_len);
	if (new_env == NULL)
		return (-1);
	ft_strlcpy(new_env, arg, new_len);
	tmp = *env_ptr;
	*env_ptr = new_env;
	free(tmp);
	tmp = NULL;
	return (0);
}

// QUESTION: the function is almost the same as copy_envp. maybe do it with one?
static int	add_env(char *arg, t_env *envp)
{
	char	**envp_old;
	char	**envp_new;
	int		i;

	envp_old = envp->env[envp->real_shlvl];
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
	envp->env[envp->real_shlvl] = envp_new;
	free_arr_of_arr(envp_old);
	return (0);
}

// PROBLEM:	why this line is in envp list?
// 			"_=/home/mmaksimo/42/home_minishell/./minishell"
// TODO: 1) check args validity
// 		 2) update envp list
// QUESTION: split to var_name, var_value?
int	ft_export(t_cmd *cmd, t_env *envp)
{
	char	**env_ptr;
	int		j;

	env_ptr = NULL;
	if (!cmd->args[1])
	{
		if (print_sorted_env(envp->env[envp->real_shlvl]) < 0)
			return (1);
		else
			return (0);
	}
	j = 1;
	while (cmd->args[j] != NULL)
	{
		if (!isvalid_arg(cmd->args[j]))
			return (1);
		env_ptr = env_exists(cmd->args[j], envp->env[envp->real_shlvl]);
		if (env_ptr != NULL && ft_strchr(cmd->args[j], '='))
			update_envp(cmd->args[j], env_ptr);
		else if (!env_ptr)
			add_env(cmd->args[j], envp);
		j++;
	}
	return (0);
}
