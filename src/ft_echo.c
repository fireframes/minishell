/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:08:11 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/20 20:26:04 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (command == NULL)
// 	return (-1);

// ALL COMMAND INPUT ARGUMENTS GO IN AS 1 STRING
// cmd: echo $SHELL ss SD//SAD
// ret: /bin/zsh ss SD//SAD

// parse the command arg string to expand $
// the string for echo is the whole string
// how do we know it's just -n for args[1]

// check argument count

// use printf or write ?

int	ft_echo(t_command *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}