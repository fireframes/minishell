/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 13:40:44 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_struct(t_command *cmd_struc, int index)
{
	cmd_struc[index].args = NULL;
	cmd_struc[index].cmd_path = NULL;
	cmd_struc[index].command_index = 0;
	cmd_struc[index].is_builtin = false;
	cmd_struc[index].path_found = false;
	cmd_struc[index].pipes = NULL;
	cmd_struc[index].pid = 0;
	cmd_struc[index].read_fd = 0;
	cmd_struc[index].write_fd = 0;
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
		init_struct(cmds_struc, i);
		i++;
	}
	return (cmds_struc);
}

// QUESTION: should freeing mallocated memory have its own module instead
//	of being inside execution module?
void	main_module(char **envp, char *read_line, char *prompt_with_path)
{
	t_command	*cmds_struc;

	cmds_struc = NULL;
	add_history(read_line);
	cmds_struc = parsing_module(envp, read_line, cmds_struc);
	execution_module(cmds_struc, envp);
	free_module(cmds_struc, read_line, prompt_with_path);
}

// NOTE: based on current implementation of ft_pwd, taking the same assumptions
// -> should be modified if ft_pwd (esp. regarding buffer size)
static char	*get_curr_dir(void)
{
	static char	curr_dir[PATH_MAX + 1];
	char		*full_prompt;

	full_prompt = strjoin_v2(getcwd(curr_dir, sizeof(curr_dir)), "$ ");
	return (full_prompt);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt_with_path;

	(void) argv;
	if (argc != 1)
		return (1);
	while (1)
	{
		prompt_with_path = get_curr_dir();
		read_line = readline(prompt_with_path);
		if (!read_line)
			break ;
		if (*read_line)
			main_module(envp, read_line, prompt_with_path);
	}
	return (0);
}
