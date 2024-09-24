/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:41:40 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/24 20:30:29 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO:

// if no args go to HOME
// parse string to check if correct path ?
// use access to check if path exists ?

// if args[2] exists, what error? "cd: string not in pwd: ./src"
// add logic for relative and absolute
// change shell representation of current working dir
// autocomplete ?
// perror or printf ?

#include "minishell.h"

static bool	isvalidpath(char *path)
{
	if (path[0] == '.')
		return (true);
	else if (path[0] == '/')
		return (true);
	return (false);
}

static bool	chdir_home(void)
{
	char	*homedir;

	homedir = getenv("HOME");
	if (homedir == NULL)
	{
		perror("cd: getenv() error:");
		return (false);
	}
	else if (chdir(homedir) != 0)
	{
		printf("chdir() to %s failed\n", homedir);
		return (false);
	}
	return (true);
}

int	ft_cd(t_command *cmd)
{
	if (cmd->args[1] == NULL)
	{
		if (chdir_home())
			return (0);
		else
			return (-1);
	}
	else if (cmd->args[2])
	{
		printf("cd: string not in pwd: %s\n", cmd->args[1]);
		return (-1);
	}
	else if (!isvalidpath(cmd->args[1]))
	{
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		return (-1);
	}
	else if (chdir(cmd->args[1]) != 0)
	{
		printf("chdir() to %s failed\n", cmd->args[1]);
		return (1);
	}
	return (0);
}
