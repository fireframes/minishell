/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 18:02:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: since we are not mallocing read_line, should we free it?
// ANSWER: readline() function is doing that for us actually
void	free_module(t_cmd *cmds_struc, char *read_line, char *prmpt_path)
{
	free_structs(cmds_struc);
	free(prmpt_path);
	free(read_line);
}

void	free_arr_of_arr(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	free_structs(t_cmd *cmds_struc)
{
	int	i;

	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		free_arr_of_arr(cmds_struc[i].args);
		free(cmds_struc[i].cmd_path);
		cmds_struc[i].cmd_path = NULL;
		i++;
	}
	free_arr_of_arr(cmds_struc->cmds_splits);
	free(cmds_struc->pipes);
	free(cmds_struc);
	cmds_struc = NULL;
}
