/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:05:13 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 18:02:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	check_minishell_call(t_cmd *command)
// {
// 	if (ft_strcmp(command->args[0], "") == 0)
// }

bool	check_builtin(t_cmd *command)
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(command->args[0], "export") == 0)
		return (true);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(command->args[0], "env") == 0)
		return (true);
	else if (ft_strcmp(command->args[0], "exit") == 0)
		return (true);
	return (false);
}
