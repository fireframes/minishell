/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/05 15:47:32 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isvalid_arg(char *arg)
{
	char	*arg_tmp;

	if (*arg == '=')
	{
		printf("export: `%s`: not a valid identifier\n", arg);
		return (false);
	}
	arg_tmp = arg;
	while (*arg_tmp != '=' && *arg_tmp)
	{
		if (!ft_isalnum(*arg_tmp))
		{
			printf("export: `%s` not a valid identifier\n", arg);
			return (false);
		}
		arg_tmp++;
	}
	return (true);
}

// 1. update path with totally new path
// 2. concatenate to old path
// 3. if empty == ""
int	update_envp(char *arg, char **env_ptr)
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
			return (-1);
		else
			return (0);
	}
	j = 1;
	while (cmd->args[j] != NULL)
	{
		if (!isvalid_arg(cmd->args[j]))
			return (-1);
		env_ptr = env_exists(cmd->args[j], envp->env[envp->real_shlvl]);
		if (env_ptr != NULL && ft_strchr(cmd->args[j], '='))
			update_envp(cmd->args[j], env_ptr);
		else if (!env_ptr)
			add_env(cmd->args[j], envp);
		j++;
	}
	return (0);
}
