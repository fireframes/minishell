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

// TODO wrap the if(...) into command_error()
// TODO take into account relative and absolute commands paths too!
// BIG PARSING MODULE!
// Parsing just before the split call?
// 'free_split(commands->cmds_split)' has been deleted the line before printf
// TODO problem with double free when trying an unexisting command
void	cmds_parse(t_command *commands, char **envp)
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
			commands[i].cmd_path = find_command_path(commands[i].args[0], envp,
					&commands->cmds_splits[i]);
			if (!commands[i].cmd_path)
			{
				printf("command not found: %s\n", commands[i].args[0]);
// free_commands(commands, commands->total_cmds);
				commands[i].path_found = false;
			}
			else
				commands[i].path_found = true;
		}
		i++;
	}
}
