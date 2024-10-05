/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/02 19:30:52 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_module(t_cmd *cmds_struc, t_env *envp)
{
	if (cmds_struc->total_cmds == 1 && cmds_struc->is_builtin == true)
		execute_builtin(cmds_struc, envp);
	else if (cmds_struc->total_cmds == 1 && cmds_struc->minishell_call == true)
	{
		init_pipes(cmds_struc);
		incr_or_decr_env_shlvl(envp->env[envp->real_shlvl], true);
	}	
	else
	{
		init_pipes(cmds_struc);
		forking(cmds_struc, envp);
	}
}

// TODO: error check to be added in the loops
// TODO: this function is more than 25 lines and it messes with norm
// IMPORTANT FOR MAXIM: please check if what is sent to ft_env (which should
//	be the same as before switching to the struc_env instead of char ***envp)
//	still make sense (and is up to date with the last existing copy of env)
void	execute_builtin(t_cmd *cmd, t_env *envp)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(cmd, envp->env);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(cmd, envp->env[0]);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd, envp);
		// ft_exit(envp);
	return ;
}
