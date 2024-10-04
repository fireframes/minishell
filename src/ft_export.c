/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:39:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/04 14:04:10 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isvalid_arg(char *arg)
{
	(void) arg;
	return (true);
}

void	update_envp(char *arg, char ***envp, char *env_ptr)
{
	(void) arg;
	(void) envp;

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
		{
			printf("export: not valid in this context: %s\n", cmd->args[j]);
			return (-1);
		}
		env_ptr = env_exists(cmd->args[j], *envp);
		if (env_ptr != NULL)
			update_envp(cmd->args[j], envp, env_ptr);
		else
			add_env(cmd->args[j], envp);
		j++;
	}
	return (0);
}
