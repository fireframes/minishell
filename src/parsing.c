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

t_command	*parsing_module(char **envp, char *read_line)
{
	t_command	*commands;
	char		**cmds_splits;

	cmds_splits = cmds_parse(read_line);
	commands = init_struct(cmds_splits);
	cmd_args_parse(commands, envp);
	return (commands);
}

char	**cmds_parse(char *read_line)
{
	char		**cmds_splits;

	cmds_splits = NULL;
	cmds_splits = split_v2(read_line, '|');
	return (cmds_splits);
}

// TODO wrap the if(...) into command_error()
// TODO take into account relative and absolute commands paths too!
// BIG PARSING MODULE!
// Parsing just before the split call?
// 'free_split(commands->cmds_split)' has been deleted the line before printf
// TODO problem with double free when trying an unexisting command
void	cmd_args_parse(t_command *commands, char **envp)
{
	int	i;

	i = 0;
	while (i < commands->total_cmds)
	{
		commands[i].command_index = i;
		commands[i].args = split_v2(commands->cmds_splits[i], ' ');
		if (check_builtin(&commands[i]))
			commands[i].is_builtin = true;
		else
		{
			commands[i].is_builtin = false;
			commands[i].cmd_path = find_command_path(commands[i].args[0], envp);
			if (!commands[i].cmd_path)
			{
				printf("command not found: %s\n", commands[i].args[0]);
				commands[i].path_found = false;
			}
			else
				commands[i].path_found = true;
		}
		i++;
	}
}
