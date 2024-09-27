/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:58:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 18:02:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// is the buffer size appropriate -- check again
// is there a purpose of returning -1 if too many args?
int	ft_pwd(t_cmd *cmd)
{
	char	curpath[PATH_MAX + 1];

	if (cmd->args[1])
	{
		perror("pwd: too many arguments");
		return (-1);
	}
	if (getcwd(curpath, sizeof(curpath)) == NULL)
		perror("pwd: getcwd() error");
	else
		printf("%s\n", curpath);
	return (0);
}
