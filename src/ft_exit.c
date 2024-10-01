/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 17:11:50 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_first_levels(char** envp)
{
    int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strnstr_v2(envp[i], "SHLVL=", 6) && envp[i])
			break ;
		i++;
	}
    if (ft_strcmp(envp[i], "SHLVL=2") == 0)
        return (true);
    else if (ft_strcmp(envp[i], "SHLVL=1") == 0) 
        return (true);
    else
        return (false);
}

// QUESTIONS: what is the maximum exit code number possible? What happens if
//  you have value higher? A negative value?
// TODO: Implement behavior to overflow (to 0) when higher or equal to 256;
// TODO: ...and reverse "overflowing" behavior when negative value;
// TODO: Error message if more than one parameter, if non numerical value;
static int get_second_arg(t_cmd *cmd)
{
    int exit_code_if_any;

    exit_code_if_any = 0;
    if (cmd->args[1] != NULL)
        exit_code_if_any = ft_atoi_v2(cmd->args[1]);
    return (exit_code_if_any);
}

// TODO: implement the value that can be passed as parameters (exit code)
// TODO: finish behavior when not on the lower SLVL value
// TODO: see for the max value of SLVL and what happens when overflow
// TODO: how to deal with exit code when SLVL higher thant 2?
// void    ft_exit(char **envp)
void    ft_exit(t_cmd *cmd, char **envp)
{
    int exit_code;

    exit_code = get_second_arg(cmd);
    if (is_first_levels(envp))
    {
        printf("exit\n");
        // exit (0);
        exit (exit_code);
    }
    else
    {
        printf("exit\n");
    }
}
