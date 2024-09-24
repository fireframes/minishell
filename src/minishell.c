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

// QUESTION: THE FOLLOWING FUNCTION IS NOT USED, TO BE DELETED?
// int	error_check(int ret_val, const char *err_msg, int close_fd)
// {
// 	if (ret_val == -1)
// 	{
// 		perror(err_msg);
// 		if (close_fd > 0)
// 			close(close_fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

// TODO: PARSING!
// QUESTION: protection needed after split call (if (!prompt_split)...)?
// QUESTION: do we have access to the cmds_splits and total_cmds struct var
//  defined in the array we use later (such commands[i])?
// void	execute_cmd(char *read_line, char **envp)
//	!!! CHANGE for:
t_command	*init_global(char *read_line)
{
	char		**cmds_splits;
	int			cmd_count;
	t_command	*commands;
	int			i;

	cmd_count = 0;
	cmds_splits = NULL;
	cmds_splits = split_v2(read_line, '|');
	while (cmds_splits[cmd_count])
		cmd_count++;
	commands = malloc(sizeof(t_command) * cmd_count);
	if (!commands)
		free_split(cmds_splits);
	commands->cmds_splits = cmds_splits;
	commands->total_cmds = cmd_count;
	i = 0;
	while (i < commands->total_cmds)
	{
		commands[i].cmds_splits = commands->cmds_splits;
		commands[i].total_cmds = commands->total_cmds;
		i++;
	}
	return (commands);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
// QUESTION: Do erroneous command go to history?
// TODO: handle errors here?
// QUESTION: since we are not mallocing read_line, should we free it?
// IMPORTANT: if no path [and it is not a builtin], do not execute process
//	after the cmds_parse call [?]
// cmds_parse should be migrated to the Parsing Module
// parsing shoudl be done on the init_global call line [or just after/before]
void	terminal_prompt(char **envp)
{
	char		*read_line;
	t_command	*commands;

	while (1)
	{
		read_line = readline(">> ");
		if (!read_line)
			break ;
		if (*read_line)
		{
			add_history(read_line);
			commands = init_global(read_line);
			cmds_parse(commands, envp);
			if (commands->is_builtin && commands->total_cmds == 1)
				execute_builtin(commands);
			else
			{
				init_pipes(commands);
				forking(commands, envp);
			}
		}
		free(read_line);
	}
}

int	main(int argc, char **envp)
{
	if (argc != 1)
		return (1);
	terminal_prompt(envp);
	return (0);
}
