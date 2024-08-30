/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/08/30 20:54:49 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

typedef struct s_fpids
{
	int		file[2];
	int		pipefd[2];
	pid_t	pid[2];
}			t_fpids;


typedef struct s_cmdargs
{
	char	**bin_path;
	char	**cmd_argv;
	char	*cmd_path;
	int		exit_status;
}	t_cmdargs;

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
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	child_process()
{
	t_cmdargs	cmdargs;
	int			n;

	n = child_id;
	cmdargs = find_command_path(argv, envp, argv);

	// if (cmdargs.exit_status == 1)
	// {
	// 	close_fpids(fp_id, n);
	// 	exit(EXIT_FAILURE);
	// }
	// error_check(dup2(fp_id.file[n], n), "dup2", fp_id.file[n]);
	// error_check(dup2(fp_id.pipefd[1 - n], 1 - n), "dup2", fp_id.pipefd[1 - n]);
	// close_fpids(fp_id, n);
	// error_check(execve(cmdargs.cmd_path, cmdargs.cmd_argv, envp), "execve", 0);
}

bool	execute_cmd(char *read_line, char **envp)
{
	char 	**prompt_split;
	char 	*cmd_path;

	if (!read_line)
		return (false);
	prompt_split = split_v2(read_line, '|');
	if (!prompt_split)
		return (false);

	// get number of commands
	int cmd_cnt = 0;
	while (prompt_split[cmd_cnt])
		cmd_cnt++;

	// allocate array of pipes and fork processes
	if (cmd_cnt > 1)
	{
		int (*pipes)[2] = NULL;

		pipes = malloc(sizeof(*pipes) * (cmd_cnt - 1));
		if (!pipes)
		{
			free_split(prompt_split);
			return (false);
		}
		// create pipes
		int i = 0;
		while (i < cmd_cnt - 1)
		{
			if (pipe(pipes[i]) == -1)
			{
				free_split(prompt_split);
				free(pipes);
				return (false);
			}
			i++;
		}
		// fork processes
		i = 0;

		while (i < cmd_cnt)
		{
			pid_t	pid = fork();
			// error check

			if (pid == 0)
				child_process(prompt_split[i], envp, pipes[i], i);


				int i = 0;
				while (prompt_split[i])
				{
					cmd_path = find_command_path(prompt_split[i][0], envp, prompt_split[i]);
					if (!cmd_path)
					{
						printf("command not found: %s\n", prompt_split[i]);
						free_split(prompt_split);
						return (false);
					}
					i++;
				}
			i++;
		}

	}


	return (true);
}

void	terminal_line(char **envp)
{
	char	*read_line = NULL;

	while (1) // TODO exit loop with SIGNALS
	{
		read_line = readline(">> ");

		execute_cmd(read_line, envp);
		if (read_line && *read_line)
		{
			//NOTE - is history implemented here?
			add_history(read_line);
			free(read_line);
			read_line = NULL;
		}
	}
}

int	main(int argc, char **envp)
{
	if (argc != 1)
		return (1);

	terminal_line(envp);

	return (0);
}
