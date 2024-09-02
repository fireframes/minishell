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

void	child_process(t_command cmd, int read_fd, int write_fd, char **envp)
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

void	execute_cmd(char *read_line, char **envp)
{
	char		**prompt_split;
	int			cmd_count;
	t_command	*commands;

	cmd_count = 0;
	prompt_split = split_v2(read_line, '|');
	// if (!prompt_split)
	while (prompt_split[cmd_count])
		cmd_count++;
	commands = malloc(sizeof(t_command) * cmd_count);
	if (!commands)
	{
		free_split(prompt_split);
	}
	commands->total_commands = cmd_count;

//	DIVIDE FUNCTION HERE
 
	int i = 0;
	while (i < cmd_count)
	{
		commands[i].args = split_v2(prompt_split[i], ' ');
		commands[i].cmd_path = find_command_path(commands[i].args[0], envp, &prompt_split[i]);
		commands[i].command_index = i;
		// TODO wrap into command_error()
		if (!commands[i].cmd_path)
		{
			printf("command not found: %s\n", commands[i].args[0]);
			free_commands(commands, cmd_count);
			free_split(prompt_split);
		}
		i++;
	}

	int (*pipes)[2];

	pipes = malloc(sizeof(*pipes) * (cmd_count - 1));
	if (!pipes)
	{
		free_commands(commands, cmd_count);
	}

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_commands(commands, cmd_count);
			free_split(prompt_split);

		}
		i++;
	}

	// Fork child processes
	pid_t	pid;
	int		read_fd;
	int		write_fd;

	i = 0;

	while (i < cmd_count)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			// TODO: handle error, close pipes, free resources, etc...
			free_commands(commands, cmd_count);
			free_split(prompt_split);

		}
		else if (pid == 0)
		{
			// Child process
			if (i == 0)
				read_fd = STDIN_FILENO;
			else
				read_fd = pipes[i - 1][0];

			if (i == cmd_count - 1)
				write_fd = STDOUT_FILENO;
			else
				write_fd = pipes[i][1];

			// Close unused pipe ends
			int j = 0;
			while (j < cmd_count - 1)
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
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}

	// Free allocated resources
	free_commands(commands, cmd_count);
	free_split(prompt_split);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
// QUESTION: Do erroneous command go to history?
// TODO: handle errors here?
// QUESTION: since we are not mallocing read_line, should we free it?
void terminal_prompt(char **envp)
{
	char *read_line;

	while (1)
	{
		read_line = readline(">> ");
		if (!read_line)
			break ;
		if (*read_line)
		{
			add_history(read_line);
			// split_and_count_pipes(read_line);
			execute_cmd(read_line, envp);
		}
		free(read_line);
	}
}

int main(int argc, char **envp)
{
	if (argc != 1)
		return 1;
	terminal_prompt(envp);
	return (0);
}
