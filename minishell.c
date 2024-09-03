/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/08/28 15:14:10 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char *read_line, char **envp)
{
	char 	**prompt_elements;
	char 	*cmd_path;
	pid_t	child_pid;

//	split with |
// create children
	prompt_elements = split_v2(read_line, ' ');
	cmd_path = find_command_path(prompt_elements[0], envp, prompt_elements);
	child_pid = fork();
	if (child_pid == 0)
		execve(cmd_path, prompt_elements, NULL);
	waitpid(child_pid, NULL, 0);
//	free split with |
}

char *terminal_line(char *read_line, char **envp)
{
	while (1) // TODO exit loop with SIGNALS
	{
		if (read_line)
		{
//			free(read_line); // NOTE - useless if read_line is a static var
			read_line = NULL;
		}
		read_line = readline(">> ");
		execute_cmd(read_line, envp);
		if (read_line && *read_line) //NOTE - is history implemented here?
			add_history(read_line);
	}
	return (read_line);
}

int	main(int argc, char **envp)
{
	(void)	argc;
	//(void)	envp; // TODO 0. extract envvar
	static char	*read_line = NULL; // NOTE - keep it static? GNU doc

	read_line = terminal_line(read_line, envp);
	if (read_line)
	{
		free(read_line);
		read_line = NULL;
	}
	return (0);
}
