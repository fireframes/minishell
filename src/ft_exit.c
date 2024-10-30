/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/25 22:19:47 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTIONS: what is the maximum exit code number possible? What happens if
//  you have value higher? A negative value?
// TODO: Implement behavior to overflow (to 0) when higher or equal to 256;
// TODO: ...and reverse "overflowing" behavior when negative value;
// TODO: Error message if more than one parameter, if non numerical value;
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

// TODO: implement the value that can be passed as parameters (exit code)
// TODO: finish behavior when not on the lower SLVL value
// TODO: see for the max value of SLVL and what happens when overflow
// TODO: how to deal with exit code when SLVL higher thant 2?
// void    ft_exit(char **envp)
// TODO: the last line in the last else was:
//		incr_or_decr_env_shlvl(envp->env[envp->real_shlvl], false);
// TODO IMPORTANT: when you there is an error code and you exit totally
//	minishell the exit status displayed in bash should be the error code and
//	not the success of the exit command!
int	ft_exit(t_cmd *cmd, t_env *envp, char *read_line, char *prompt)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (cmd)
		exit_code = error_module(exit_code, cmd);
	if (envp->real_shlvl == 0)
	{
		free_on_exit(&envp, NULL);
		free_module(cmd, read_line, prompt);
		exit(exit_code);
	}
	else
	{
		envp->env[envp->real_shlvl] = NULL;
		envp->real_shlvl--;
	}
	return (exit_code);
}
