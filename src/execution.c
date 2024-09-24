/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/24 15:26:16 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: error check to be added in the loops
void	execute_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
	{
		ft_echo(cmd);
	}
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		ft_pwd(cmd);
		return ;
	}
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return ;
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return ;
}
