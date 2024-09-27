/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 13:43:22 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_module(t_command *cmds_struc, char **envp)
{
	if (cmds_struc->total_cmds == 1 && cmds_struc->is_builtin == true)
		execute_builtin(cmds_struc, envp);
	else
	{
		init_pipes(cmds_struc);
		forking(cmds_struc, envp);
	}
}

// TODO: error check to be added in the loops
// TODO: this function is more than 25 lines and it messes with norm
void	execute_builtin(t_command *cmd, char **envp)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		ft_echo(cmd);
		return ;
	}
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		ft_cd(cmd);
		return ;
	}
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		ft_pwd(cmd);
		return ;
	}
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
	{
		ft_env(cmd, envp);
		return ;
	}
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return ;
}
