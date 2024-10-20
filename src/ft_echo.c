/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:08:11 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/15 16:04:10 by mmaksimo         ###   ########.fr       */
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

// check argument count?

// use printf or write? currently output is not recognized when piping

// EXPANDER should expand $ in any case!

int	ft_echo(t_cmd *cmd)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
