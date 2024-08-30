/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/08/30 22:16:34 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <sys/wait.h>

typedef struct	s_command
{
	char **args;
	char *cmd_path;
}	t_command;

int	error_check(int ret_val, const char *err_msg, int close_fd)
{
	if (ret_val == -1)
	{
		perror(err_msg);
		if (close_fd > 0)
			close(close_fd);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	free_split(char **split)
{
	int i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_commands(t_command *commands, int cmd_cnt)
{
	int i = 0;
	while (i < cmd_cnt)
	{
		free_split(commands[i].args);
		free(commands[i].cmd_path);
		commands[i].cmd_path = NULL;
		i++;
	}
	free(commands);
	commands = NULL;
}

void child_process(t_command cmd, int read_fd, int write_fd, char **envp)
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
	execve(cmd.cmd_path, cmd.args, envp);
	// TODO: handle error, close pipes, free resources, etc...
	perror("execve");
	exit(EXIT_FAILURE);
}

bool execute_cmd(char *read_line, char **envp)
{
	char		**prompt_split;
	int			cmd_cnt;
	t_command	*commands;

	cmd_cnt = 0;

	prompt_split = split_v2(read_line, '|');
	if (!prompt_split)
		return (false);

	while (prompt_split[cmd_cnt])
		cmd_cnt++;

	commands = malloc(sizeof(t_command) * cmd_cnt);
	if (!commands)
	{
		free_split(prompt_split);
		return (false);
	}

	int i = 0;
	while (i < cmd_cnt)
	{
		commands[i].args = split_v2(prompt_split[i], ' ');
		commands[i].cmd_path = find_command_path(commands[i].args[0], envp, &prompt_split[i]);
		// TODO wrap into command_error()
		if (!commands[i].cmd_path)
		{
			printf("command not found: %s\n", commands[i].args[0]);
			free_commands(commands, cmd_cnt);
			free_split(prompt_split);
			return (false);
		}
		i++;
	}

	int (*pipes)[2];

	pipes = malloc(sizeof(*pipes) * (cmd_cnt - 1));
	if (!pipes)
	{
		free_commands(commands, cmd_cnt);
		return (false);
	}

	i = 0;
	while (i < cmd_cnt - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_commands(commands, cmd_cnt);
			free_split(prompt_split);

		}
		i++;
	}

	// Fork child processes
	pid_t	pid;
	int		read_fd;
	int		write_fd;

	i = 0;

	while (i < cmd_cnt)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			// TODO: handle error, close pipes, free resources, etc...
			free_commands(commands, cmd_cnt);
			free_split(prompt_split);

			return (false);
		}
		else if (pid == 0)
		{
			// Child process
			if (i == 0)
				read_fd = STDIN_FILENO;
			else
				read_fd = pipes[i - 1][0];

			if (i == cmd_cnt - 1)
				write_fd = STDOUT_FILENO;
			else
				write_fd = pipes[i][1];

			// Close unused pipe ends
			int j = 0;
			while (j < cmd_cnt - 1)
			{
				if (j != i - 1)
					close(pipes[j][0]);
				if (j != i)
					close(pipes[j][1]);
				j++;
			}
			child_process(commands[i], read_fd, write_fd, envp);
		}
		i++;
	}

	// PARENT PROCESS
	// Close all pipe ends and wait for all child processes to finish
	i = 0;
	while (i < cmd_cnt - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	i = 0;
	while (i < cmd_cnt)
	{
		wait(NULL);
		i++;
	}

	// Free allocated resources
	free_commands(commands, cmd_cnt);
	free_split(prompt_split);
	return (true);
}

void terminal_line(char **envp)
{
	char *read_line = NULL;

	while (1) // TODO: exit loop with SIGNALS
	{
		read_line = readline(">> ");
		if (!read_line)
			break ;  // EOF (Ctrl+D)

		if (*read_line)
		{
			add_history(read_line);
			execute_cmd(read_line, envp);
			// TODO: handle error
		}
		free(read_line);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void) argv;
	if (argc != 1)
		return 1;

	terminal_line(envp); // TODO: handle errors ?

	return 0;
}
