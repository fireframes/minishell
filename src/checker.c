/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:05:13 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/21 19:24:41 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_builtin(t_cmd *command)
{
	if (ft_strncmp(command->args[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(command->args[0], "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(command->args[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(command->args[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(command->args[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(command->args[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(command->args[0], "exit", 4) == 0)
		return (true);
	return (false);
}
