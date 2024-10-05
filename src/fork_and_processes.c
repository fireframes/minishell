/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/05 15:21:15 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: do we have to call this function when only one command (no pipes)?
// QUESTION: if there is no pipes, shouldn't it be null (and not malloced?)?
void	init_pipes(t_cmd *cmds_struc)
{
	int	(*pipes)[2];
	int	i;

	pipes = NULL;
	pipes = malloc(sizeof(*pipes) * (cmds_struc->total_cmds - 1));
	if (!pipes)
		free_structs(cmds_struc);
	cmds_struc->pipes = pipes;
	i = 0;
	while (i < cmds_struc->total_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_structs(cmds_struc);
		}
		i++;
	}
}

// TODO: handle error, close pipes, free resources, etc...
void	exec_cmd(t_cmd cmds_struc, int read_fd, int write_fd, t_env *envp)
{
	if (read_fd != STDIN_FILENO)
	{
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
	}
	if (write_fd != STDOUT_FILENO)
	{
		dup2(write_fd, STDOUT_FILENO);
		close(write_fd);
	}
	if (cmds_struc.is_builtin)
	{
		execute_builtin(&cmds_struc, envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(cmds_struc.cmd_path, cmds_struc.args, envp->env[0]);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_cmd *cmds_struc)
{
	int	i;

	i = 0;
	while (i < cmds_struc->total_cmds - 1)
	{
		close(cmds_struc->pipes[i][0]);
		close(cmds_struc->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		wait(NULL);
		i++;
	}
}

void	child_process(t_cmd *cmds_struc, int i, t_env *envp)
{
	int		j;

	if (i == 0)
		cmds_struc[i].read_fd = STDIN_FILENO;
	else
		cmds_struc[i].read_fd = cmds_struc->pipes[i - 1][0];
	if (i == cmds_struc->total_cmds - 1)
		cmds_struc[i].write_fd = STDOUT_FILENO;
	else
		cmds_struc[i].write_fd = cmds_struc->pipes[i][1];
	j = 0;
	while (j < cmds_struc->total_cmds - 1)
	{
		if (j != i - 1)
			close(cmds_struc->pipes[j][0]);
		if (j != i)
			close(cmds_struc->pipes[j][1]);
		j++;
	}
	if (cmds_struc[i].path_found == true || cmds_struc[i].is_builtin == true)
		exec_cmd(cmds_struc[i], cmds_struc[i].read_fd, cmds_struc[i].write_fd,
			envp);
}

// TODO: execute builtin without forking it
void	forking(t_cmd *cmds_struc, t_env *envp)
{
	int		i;

	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		if ((cmds_struc[i].path_found == true
				|| cmds_struc[i].is_builtin == true)
			&& cmds_struc[i].minishell_call != true)
		{
			cmds_struc[i].pid = fork();
			if (cmds_struc[i].pid == -1)
			{
				perror("fork");
				free_structs(cmds_struc);
			}
			else if (cmds_struc[i].pid == 0)
				child_process(cmds_struc, i, envp);
		}
		i++;
	}
	parent_process(cmds_struc);
}
