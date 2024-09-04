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

// QUESTION: protection needed after split call (if (!prompt_split)...)?
// void	execute_cmd(char *read_line, char **envp)
//	!!! CHANGE for: 
t_command	*init_global_and_pipes(char *read_line)
{
	char		**cmds_split;
	int			cmd_count;
	t_command	*commands;

	cmd_count = 0;
	cmds_split = NULL;
	cmds_split = split_v2(read_line, '|');
	while (cmds_split[cmd_count])
		cmd_count++;
	commands = malloc(sizeof(t_command) * cmd_count);
	if (!commands)
		free_split(cmds_split);
	commands->cmds_split = cmds_split;
	commands->total_cmds = cmd_count;
	return (commands);
}

// TODO wrap the if(...) into command_error()
void	cmds_path(t_command *commands, char **envp)
{
	int i = 0;

	while (i < commands->total_cmds)
	{
		commands[i].args = split_v2(commands->cmds_split[i], ' ');
		commands[i].cmd_path = find_command_path(commands[i].args[0], envp, &commands->cmds_split[i]);
		commands[i].command_index = i;
		if (!commands[i].cmd_path)
		{
			printf("command not found: %s\n", commands[i].args[0]);
			// free_split(commands->cmds_split);
			free_commands(commands, commands->total_cmds);
			commands[i].path_found = false;
		}
		else
			commands[i].path_found = true;
		i++;
	}
}

void	init_pipes(t_command *commands, char **envp)
{
	int (*pipes)[2];
	int i;

	pipes = malloc(sizeof(*pipes) * (commands->total_cmds - 1));
	if (!pipes)
	{
		free_commands(commands, commands->total_cmds);
	}

	i = 0;
	while (i < commands->total_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_commands(commands, commands->total_cmds);
			free_split(commands->cmds_split);
		}
		i++;
	}

//	!!! DIVIDE FUNCTION HERE???

	// Fork child processes
	pid_t	pid;
	int		read_fd;
	int		write_fd;

	i = 0;

	while (i < commands->total_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			// TODO: handle error, close pipes, free resources, etc...
			free_commands(commands, commands->total_cmds);
			free_split(commands->cmds_split);

		}
		else if (pid == 0)
		{
			// Child process
			if (i == 0)
				read_fd = STDIN_FILENO;
			else
				read_fd = pipes[i - 1][0];

			if (i == commands->total_cmds - 1)
				write_fd = STDOUT_FILENO;
			else
				write_fd = pipes[i][1];

			// Close unused pipe ends
			int j = 0;
			while (j < commands->total_cmds - 1)
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

//	!!! DIVIDE FUNCTION HERE???

	// PARENT PROCESS
	// Close all pipe ends and wait for all child processes to finish
	i = 0;
	while (i < commands->total_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	i = 0;
	while (i < commands->total_cmds)
	{
		wait(NULL);
		i++;
	}
	// Free allocated resources
	free_split(commands->cmds_split);
	free_commands(commands, commands->total_cmds);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
// QUESTION: Do erroneous command go to history?
// TODO: handle errors here?
// QUESTION: since we are not mallocing read_line, should we free it?
void terminal_prompt(char **envp)
{
	char *read_line;
	t_command	*commands;

	while (1)
	{
		read_line = readline(">> ");
		if (!read_line)
			break ;
		if (*read_line)
		{
			add_history(read_line);
			commands = init_global_and_pipes(read_line);
			cmds_path(commands, envp);
			// IMPORTANT: if no path, do not execute the remaining process
			init_pipes(commands, envp);
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
