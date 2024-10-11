/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:41:40 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/11 21:35:05 by mmaksimo         ###   ########.fr       */
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

// TODO: correct the behavior in which it does not go into an existing
//	directory, saying: "cd: no such file or directory: <name>"

#include "minishell.h"

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
		printf("cd: chdir() to %s failed", homedir);
		return (false);
	}
	return (true);
}

int	ft_cd(t_cmd *cmd)
{
	if (cmd->args[1] == NULL)
	{
		if (chdir_home())
			return (0);
		else
			return (1);
	}
	else if (cmd->args[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	else if (chdir(cmd->args[1]) != 0)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		// printf("cd:  %s: No such file or directory\n", cmd->args[1]);
		return (1);
	}
	return (0);
}
