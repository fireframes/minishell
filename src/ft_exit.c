/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:27:05 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_2nd_arg(t_cmd *cmd)
{
	int	exit_code_if_any;

	exit_code_if_any = 0;
	if (cmd->args[1] != NULL)
		exit_code_if_any = atoi_v2(cmd->args[1]);
	exit_code_if_any = exit_code_if_any % 256;
	return (exit_code_if_any);
}

static int	check_error(t_cmd *cmd)
{
	int	index;

	index = 0;
	if (cmd->args[1] != NULL)
	{
		if (cmd->args[1][index] == '+' || cmd->args[1][index] == '-')
			index++;
		while (cmd->args[1][index] != '\0')
		{
			if (ft_isdigit_v3(cmd->args[1][index]) == 0)
				return (2);
			index++;
		}
		if (cmd->args[1] != NULL)
			if (cmd->args[2] != NULL)
				return (1);
	}
	return (0);
}

static int	error_module(int exit_code, t_cmd *cmd)
{
	exit_code = get_2nd_arg(cmd);
	if (check_error(cmd) == 1)
	{
		ft_putstr_fd("minishell : too many arguments\n", 2);
		exit_code = 1;
	}
	if (check_error(cmd) == 2)
	{
		ft_putstr_fd("minishell: numeric argument required\n", 2);
		exit_code = 2;
	}
	return (exit_code);
}

int	ft_exit(t_cmd *cmd, t_env *envp, char *read_line)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (cmd)
		exit_code = error_module(exit_code, cmd);
	if (envp->real_shlvl == 0)
	{
		free_on_exit(&envp);
		free_module(cmd, read_line);
		exit(exit_code);
	}
	else
	{
		free_arr_of_arr(envp->env[envp->real_shlvl]);
		envp->env[envp->real_shlvl] = NULL;
		envp->real_shlvl--;
	}
	return (exit_code);
}
