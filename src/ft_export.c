/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/04 16:22:43 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isvalid_arg(char *arg)
{
	char	*arg_tmp;

	arg_tmp = arg;
	while (*arg_tmp != '=' && *arg)
	{
		if (!ft_isalnum(*arg_tmp))
		{
			printf("export: not valid in this context: %s\n", arg);
			return (false);
		}
		arg_tmp++;
	}
	return (true);
}
// 1. update path with totally new path
// 2. concatenate to old path
void	update_envp(char *arg, char ***envp, char *env_ptr)
{
	// char *arg_offset;
	(void) arg;
	(void) envp;

	// arg_offset = arg + get_envvar_len(arg);
	// ft_strlen(env_ptr);
//
	printf("DUMMY=%s\n", env_ptr);
}

// PROBLEM:	why this line is in envp list?
// 			"_=/home/mmaksimo/42/home_minishell/./minishell"
// TODO: 1) check args validity
// 		 2) update envp list
int	ft_export(t_cmd *cmd, char ***envp)
{
	char	*env_ptr;

	env_ptr = NULL;
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
			return (-1);
		env_ptr = env_exists(cmd->args[j], *envp);
		if (env_ptr != NULL)
			update_envp(cmd->args[j], envp, env_ptr);
		else
			add_env(cmd->args[j], envp);
		j++;
	}
	return (0);
}
