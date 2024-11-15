/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:26:27 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirection(char *filename, int type)
{
	int	fd;
	int	flags;
	int	target_fd;

	if (type == 0)
	{
		flags = O_RDONLY;
		target_fd = STDIN_FILENO;
	}
	else
	{
		flags = O_WRONLY | O_CREAT;
		if (type == 2)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		target_fd = STDOUT_FILENO;
	}
	fd = open(filename, flags, 0644);
	if (fd < 0)
		return (-1);
	dup2(fd, target_fd);
	close(fd);
	return (0);
}

int	apply_redirections(char **redirs)
{
	int	i;

	if (!redirs)
		return (0);
	i = 0;
	while (redirs[i])
	{
		if (ft_strcmp(redirs[i], "<") == 0)
		{
			if (handle_redirection(redirs[i + 1], 0) < 0)
				return (-1);
		}
		else if (ft_strcmp(redirs[i], ">") == 0)
		{
			if (handle_redirection(redirs[i + 1], 1) < 0)
				return (-1);
		}
		else if (ft_strcmp(redirs[i], ">>") == 0)
		{
			if (handle_redirection(redirs[i + 1], 2) < 0)
				return (-1);
		}
		i += 2;
	}
	return (0);
}

static int	execute_builtin_command(t_cmd *cmd, t_env *envp)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd, envp));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, envp));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(cmd, envp->env[envp->real_shlvl]));
	else if (ft_strcmp(cmd->args[0], "exit") == 0 && cmd->total_cmds == 1)
		return (ft_exit(cmd, envp, NULL));
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_env *envp)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (handle_builtin_redirections(cmd) == 0)
		envp->exit_code = execute_builtin_command(cmd, envp);
	else
		envp->exit_code = 1;
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}

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
