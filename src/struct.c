/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:58:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 18:02:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_cmd *cmd_struc, int index)
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
}

// QUESTION: protection needed after split call (if (!prompt_split)...)?
t_cmd	*create_struct(char **cmds_splits, t_cmd *cmds_struc)
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
		init_struct(cmds_struc, i);
		i++;
	}
	return (cmds_struc);
}
