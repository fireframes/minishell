/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:41:40 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:26:51 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (1);
	}
	return (0);
}
