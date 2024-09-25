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
void	init_pipes(t_command *commands)
{
	int	(*pipes)[2];
	int	i;

	pipes = NULL;
	pipes = malloc(sizeof(*pipes) * (commands->total_cmds - 1));
	if (!pipes)
		free_commands(commands, commands->total_cmds);
	commands->pipes = pipes;
	i = 0;
	while (i < commands->total_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_split(commands->cmds_splits);
			free_commands(commands, commands->total_cmds);
		}
		i++;
	}
}

// TODO: handle error, close pipes, free resources, etc...
void	exec_cmd(t_command commands, int read_fd, int write_fd, char **envp)
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
	if (commands.is_builtin)
	{
		execute_builtin(&commands);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(commands.cmd_path, commands.args, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_command *commands)
{
	int	i;

	i = 0;
	while (i < commands->total_cmds - 1)
	{
		close(commands->pipes[i][0]);
		close(commands->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < commands->total_cmds)
	{
		wait(NULL);
		i++;
	}
	free_split(commands->cmds_splits);
	free_commands(commands, commands->total_cmds);
}

void	child_process(t_command *commands, int i, char **envp)
{
	int		j;

	if (i == 0)
		commands[i].read_fd = STDIN_FILENO;
	else
		commands[i].read_fd = commands->pipes[i - 1][0];
	if (i == commands->total_cmds - 1)
		commands[i].write_fd = STDOUT_FILENO;
	else
		commands[i].write_fd = commands->pipes[i][1];
	j = 0;
	while (j < commands->total_cmds - 1)
	{
		if (j != i - 1)
			close(commands->pipes[j][0]);
		if (j != i)
			close(commands->pipes[j][1]);
		j++;
	}
	if (commands[i].path_found == true || commands[i].is_builtin == true)
		exec_cmd(commands[i], commands[i].read_fd, commands[i].write_fd, envp);
}

void	forking(t_command *commands, char **envp)
{
	int		i;

	i = 0;
	while (i < commands->total_cmds)
	{
		if (commands[i].path_found == true || commands[i].is_builtin == true)
		{
			commands[i].pid = fork();
			if (commands[i].pid == -1)
			{
				perror("fork");
				free_split(commands->cmds_splits);
				free_commands(commands, commands->total_cmds);
			}
			else if (commands[i].pid == 0)
				child_process(commands, i, envp);
		}
		i++;
	}
	parent_process(commands);
}
