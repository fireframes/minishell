/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/20 20:38:59 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: protection needed after split call (if (!prompt_split)...)?
t_command	*init_struct(char **cmds_splits)
{
	int			cmd_count;
	t_command	*commands;
	int			i;

	cmd_count = 0;
	while (cmds_splits[cmd_count])
		cmd_count++;
	commands = malloc(sizeof(t_command) * cmd_count);
	if (!commands)
		free_split(cmds_splits);
	i = 0;
	while (i < cmd_count)
	{
		commands[i].cmds_splits = cmds_splits;
		commands[i].total_cmds = cmd_count;
		i++;
	}
	return (commands);
}

// QUESTION: should freeing mallocated memory have its own module instead
//	of being inside execution module?
void	main_module(char **envp, char *read_line)
{
	t_command	*commands;

	commands = NULL;
	add_history(read_line);
	commands = parsing_module(envp, read_line);
	execution_module(commands, envp);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
// QUESTION: since we are not mallocing read_line, should we free it?
int	main(int argc, char **envp)
{
	char	*read_line;

	if (argc != 1)
		return (1);
	while (1)
	{
		read_line = readline(">> ");
		if (!read_line)
			break ;
		if (*read_line)
			main_module(envp, read_line);
		free(read_line);
	}
	return (0);
}
