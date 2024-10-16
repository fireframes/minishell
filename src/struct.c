/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:58:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/15 20:18:46 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmds_struc(t_cmd *cmd_struc, int index)
{
	cmd_struc[index].args = NULL;
	cmd_struc[index].cmd_path = NULL;
	cmd_struc[index].command_index = 0;
	cmd_struc[index].is_builtin = false;
	cmd_struc[index].path_found = false;
	cmd_struc[index].minishell_call = false;
	cmd_struc[index].pipes = NULL;
	cmd_struc[index].pid = 0;
	cmd_struc[index].read_fd = 0;
	cmd_struc[index].write_fd = 0;
	cmd_struc[index].total_args = 0;
	cmd_struc[index].redir_part = NULL;
	cmd_struc[index].redir_syntax_err = false;
	cmd_struc[index].redir_amount = 0;
}

// QUESTION: protection needed after split call (if (!prompt_split)...)?
t_cmd	*create_cmds_struc(char **cmds_splits, t_cmd *cmds_struc)
{
	int			cmd_count;
	int			i;

	cmd_count = 0;
	while (cmds_splits[cmd_count])
		cmd_count++;
	cmds_struc = malloc(sizeof(t_cmd) * cmd_count);
	if (!cmds_struc)
		free_arr_of_arr(cmds_splits);
	i = 0;
	while (i < cmd_count)
	{
		cmds_struc[i].cmds_splits = cmds_splits;
		cmds_struc[i].total_cmds = cmd_count;
		init_cmds_struc(cmds_struc, i);
		i++;
	}
	return (cmds_struc);
}

void	init_env_struc(t_env *global, char **envp)
{
	global->real_shlvl = 0;
	global->env = malloc(sizeof(char **) * MAX_SHLVL);
	if (global->env == NULL)
		exit(2);
	global->env[global->real_shlvl] = copy_env(envp);
	if (global->env[global->real_shlvl] == NULL)
		exit(2);
	global->exit_code = 0;
	global->redir_syntax_err = false;
}
