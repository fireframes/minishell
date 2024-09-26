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

void	init_struct(t_command *cmd_struc)
{
	cmd_struc->args = NULL;
	cmd_struc->cmd_path = NULL;
	cmd_struc->command_index = 0;
	cmd_struc->is_builtin = false;
	cmd_struc->path_found = false;
	cmd_struc->pipes = NULL;
	cmd_struc->pid = 0;
	cmd_struc->read_fd = 0;
	cmd_struc->write_fd = 0;
}

// QUESTION: protection needed after split call (if (!prompt_split)...)?
t_command	*create_struct(char **cmds_splits, t_command *cmds_struc)
{
	int			cmd_count;
	int			i;

	cmd_count = 0;
	while (cmds_splits[cmd_count])
		cmd_count++;
	cmds_struc = malloc(sizeof(t_command) * cmd_count);
	if (!cmds_struc)
		free_arr_of_arr(cmds_splits);
	i = 0;
	while (i < cmd_count)
	{
		cmds_struc[i].cmds_splits = cmds_splits;
		cmds_struc[i].total_cmds = cmd_count;
		init_struct(cmds_struc);
		i++;
	}
	return (cmds_struc);
}

// QUESTION: should freeing mallocated memory have its own module instead
//	of being inside execution module?
void	main_module(char **envp, char *read_line)
{
	t_command	*cmds_struc;

	cmds_struc = NULL;
	add_history(read_line);
	cmds_struc = parsing_module(envp, read_line, cmds_struc);
	execution_module(cmds_struc, envp);
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
