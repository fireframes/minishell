/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:08:11 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/08 16:07:00 by mmaksimo         ###   ########.fr       */
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

char *expander(char *cmd, t_env *envp)
{
	char	*expanded;

	expanded = ft_strchr(cmd, '$');
	if (expanded && *(expanded + 1) == '?')
		printf("%d", envp->exit_code);
	return (expanded);
}

int	ft_echo(t_cmd *cmd, t_env *envp)
{
	int		i;
	int		newline;
	char	*expanded;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		expand = ft_strchr(cmd->args[i], '$');
		if (expand && *(expand + 1) == '?')
			printf("%d", envp->exit_code);
		else
			printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
