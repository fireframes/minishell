/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/01 18:31:53 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* Creates a copy of the environment variable list.
* It allocates space for the copies using static arrays,
* ensuring that copied environment variables do not exceed predefined limits.
*/
char	**copy_envp(char **envp)
{
	static char	envp_copy[ENVVAR_MAX][PATH_MAX];
	static char	*copy_ptr[ENVVAR_MAX + 1];
	int			i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (i >= ENVVAR_MAX)
		{
			perror("envp: size of envp list exceeds maximum value");
			return (NULL);
		}
		ft_strlcpy(envp_copy[i], envp[i], ft_strlen(envp[i]) + 1);
		envp_copy[i][PATH_MAX - 1] = '\0';
		copy_ptr[i] = envp_copy[i];
		i++;
	}
	copy_ptr[i] = NULL;
	return (copy_ptr);
}
