/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/24 13:25:27 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Redirections handling (not parsing, which is already done), should be done
//	in the following function.
void	execution_module(t_cmd *cmds_struc, t_env *envp)
{
	if (envp->redir_syntax_err == true)
	{
		envp->exit_code = 2;
		printf("minishell: syntax error near unexpected redirection token\n");
	}
	else if (cmds_struc->total_cmds == 1 && cmds_struc->is_builtin == true)
		execute_builtin(cmds_struc, envp);
	else if (cmds_struc->total_cmds == 1 && cmds_struc->minishell_call == true)
	{
		init_pipes(cmds_struc);
		envp->real_shlvl++;
		envp->env[envp->real_shlvl] = copy_env(envp->env[envp->real_shlvl - 1]);
		if (envp->env[envp->real_shlvl] == NULL)
			exit(2);
		incr_or_decr_env_shlvl(envp, true);
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
	int	*exit_code;

	exit_code = &envp->exit_code;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		*exit_code = ft_cd(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		*exit_code = ft_pwd();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		*exit_code = ft_export(cmd, envp);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		*exit_code = ft_unset(cmd, envp);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		*exit_code = ft_env(cmd, envp->env[envp->real_shlvl]);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		*exit_code = ft_exit(cmd, envp);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		*exit_code = ft_echo(cmd);
	return ;
}
