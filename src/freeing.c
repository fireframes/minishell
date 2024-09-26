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

void	free_in_struct(t_command *cmds_struc)
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
