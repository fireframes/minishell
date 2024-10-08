/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:19:46 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/08 15:57:17 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_shift_arr(char **env_ptr)
{
	char	**curr_env;
	char	**next_env;

	free(*env_ptr);
	curr_env = env_ptr;
	next_env = env_ptr + 1;
	while (*next_env != NULL)
	{
		*curr_env = *next_env;
		curr_env++;
		next_env++;
	}
	*curr_env = NULL;
}

int	ft_unset(t_cmd *cmd, t_env *envp)
{
	char	**env_ptr;
	int		j;

	if (!cmd->args[1])
		return (0);
	j = 1;
	while (cmd->args[j] != NULL)
	{
		env_ptr = env_exists(cmd->args[j], envp->env[envp->real_shlvl]);
		if (env_ptr != NULL && *env_ptr != NULL
			&& !ft_strchr(cmd->args[j], '='))
			free_env_shift_arr(env_ptr);
		j++;
	}
	return (0);
}
