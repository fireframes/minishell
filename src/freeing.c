/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/14 15:36:57 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_module(t_cmd *cmds_struc, char *read_line)
{
	if (cmds_struc)
		free_structs(cmds_struc);
	free(read_line);
}

void	free_arr_of_arr(char **split)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free(split);
		split = NULL;
	}
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
		if (cmds_struc[i].redirs != NULL)
			free_arr_of_arr(cmds_struc[i].redirs);
		free(cmds_struc[i].redir_part);
		i++;
	}
	free_arr_of_arr(cmds_struc->cmds_splits);
	free(cmds_struc->pipes);
	free(cmds_struc);
	cmds_struc = NULL;
}

void	free_expand(t_expnd *expand)
{
	free(expand->expanded);
	expand->expanded = NULL;
	free(expand->inquotes);
	expand->inquotes = NULL;
	free(expand);
}

void	free_on_exit(t_env **envp)
{
	free_arr_of_arr((*envp)->env[(*envp)->real_shlvl]);
	free((*envp)->env);
	(*envp)->env = NULL;
	free(*envp);
	*envp = NULL;
}
