/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 01:01:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/01 20:51:12 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_env *envp)
{
	int	i;

	if (*envp->ptr_arr == NULL)
	{
		perror("env: null or empty list");
		return (-1);
	}
	if (cmd->args[1])
	{
		printf("env: '%s': No such file or directory\n", cmd->args[1]);
		return (0);
	}
	i = 0;
	while (envp->ptr_arr[i])
	{
		printf("%s\n", envp->ptr_arr[i]);
		i++;
	}
	return (0);
}
