/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:28:45 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_shlvl_line(char **envp, int i)
{
	while (envp[i] != NULL)
	{
		if (strnstr_v2(envp[i], "SHLVL=", 6) && envp[i])
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (-1);
	return (i);
}

static int	update_shlvl_int(int shell_level_integer, bool increase)
{
	if (increase == true && shell_level_integer < 0)
		shell_level_integer = 0;
	else if (increase == true && shell_level_integer < 999)
		shell_level_integer++;
	else if (increase == true && shell_level_integer > 998)
	{
		shell_level_integer = 1;
		printf("minishell: warning: ");
		printf("shell level (1000) too high, resetting to 1\n");
	}
	else
		shell_level_integer--;
	return (shell_level_integer);
}

void	incr_or_decr_env_shlvl(t_env *envp, bool increase)
{
	int		i;
	char	*substr_1;
	char	*substr_2;
	int		shell_level_integer;

	i = 0;
	i = search_shlvl_line(envp->env[envp->real_shlvl], i);
	if (i == -1)
	{
		add_env("SHLVL=1", envp);
		return ;
	}
	substr_1 = substr_v2(envp->env[envp->real_shlvl][i], 0, 6);
	substr_2 = substr_v2(envp->env[envp->real_shlvl][i], 6, \
				strlen_v2(envp->env[envp->real_shlvl][i]) - 6);
	shell_level_integer = atoi_v2(substr_2);
	shell_level_integer = update_shlvl_int(shell_level_integer, increase);
	free(substr_2);
	substr_2 = itoa_v2(shell_level_integer);
	free(envp->env[envp->real_shlvl][i]);
	envp->env[envp->real_shlvl][i] = strjoin_v2(substr_1, substr_2);
	free(substr_1);
	free(substr_2);
}
