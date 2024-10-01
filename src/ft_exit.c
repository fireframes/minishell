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

void    ft_exit(char **envp)
{
    if (is_first_levels(envp))
    {
        printf("exit\n");
        exit (EXIT_SUCCESS);
    }
    else
    {
        printf("exit\n");
    }
}
