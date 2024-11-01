/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:58:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/21 19:11:31 by mmaksimo         ###   ########.fr       */
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
	cmd_struc[index].redirs = NULL;
	cmd_struc[index].redir_syntax_err = false;
	cmd_struc[index].redir_amount = 0;
	cmd_struc[index].last_fd_in = 0;
	cmd_struc[index].last_fd_out = 0;
	cmd_struc[index].heredocs_amount = 0;
	cmd_struc[index].env = NULL;
}

t_cmd	*create_cmds_struc(char **cmds_splits, t_cmd *cmds_struc, t_env *env)
{
	int	cmd_count;
	int	i;

	cmd_count = 0;
	while (cmds_splits != NULL && cmds_splits[cmd_count])
		cmd_count++;
	if (cmds_splits != NULL)
		cmds_struc = malloc(sizeof(t_cmd) * cmd_count);
	if (!cmds_struc || cmds_splits == NULL)
		free_arr_of_arr(cmds_splits);
	i = 0;
	while (i < cmd_count)
	{
		cmds_struc[i].cmds_splits = cmds_splits;
		cmds_struc[i].total_cmds = cmd_count;
		cmds_struc[i].env = env;
		init_cmds_struc(cmds_struc, i);
		i++;
	}
	return (cmds_struc);
}

t_env	*init_env_struc_and_shlvl(char **envp)
{
	t_env	*global;

	global = malloc(sizeof(t_env) * 1);
	if (global == NULL)
		exit(2);
	global->final_exit = false;
	global->real_shlvl = 0;
	global->env = malloc(sizeof(char **) * MAX_SHLVL);
	if (global->env == NULL)
	{
		free(global);
		exit(2);
	}
	global->env[global->real_shlvl] = copy_env(envp);
	if (global->env[global->real_shlvl] == NULL)
	{
		free(global->env);
		free(global);
		exit(2);
	}
	global->exit_code = 0;
	global->redir_syntax_err = false;
	global->total_heredocs_in_all = 0;
	incr_or_decr_env_shlvl(global, true);
	return (global);
}
