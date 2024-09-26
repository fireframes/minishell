/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/24 12:15:25 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: do we have to call this function when only one command (no pipes)?
// QUESTION: if there is no pipes, shouldn't it be null (and not malloced?)?
// QUESTION: something missing is the free following if(!pipes): free
//				cmds_split and free pipes
void	init_pipes(t_command *cmds_struc)
{
	int	(*pipes)[2];
	int	i;

	pipes = NULL;
	pipes = malloc(sizeof(*pipes) * (cmds_struc->total_cmds - 1));
	if (!pipes)
		free_commands(cmds_struc, cmds_struc->total_cmds);
	cmds_struc->pipes = pipes;
	i = 0;
	while (i < cmds_struc->total_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_split(cmds_struc->cmds_splits);
			free_commands(cmds_struc, cmds_struc->total_cmds);
		}
		i++;
	}
}

// TODO: handle error, close pipes, free resources, etc...
void	exec_cmd(t_command cmds_struc, int read_fd, int write_fd, char **envp)
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
		execute_builtin(&cmds_struc);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(cmds_struc.cmd_path, cmds_struc.args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_command *cmds_struc)
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
	free_split(cmds_struc->cmds_splits);
	free(cmds_struc->pipes);
	free_commands(cmds_struc, cmds_struc->total_cmds);
}

void	child_process(t_command *cmds_struc, int i, char **envp)
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

void	forking(t_command *cmds_struc, char **envp)
{
	int		i;

	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		if (cmds_struc[i].path_found == true || cmds_struc[i].is_builtin
			== true)
		{
			cmds_struc[i].pid = fork();
			if (cmds_struc[i].pid == -1)
			{
				perror("fork");
				free_split(cmds_struc->cmds_splits);
				free_commands(cmds_struc, cmds_struc->total_cmds);
			}
			else if (cmds_struc[i].pid == 0)
				child_process(cmds_struc, i, envp);
		}
		i++;
	}
	parent_process(cmds_struc);
}
