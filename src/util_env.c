/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/02 18:56:23 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_env_count(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	**copy_env_arr(char **envp)
{
	char	**envp_new;
	int		i;

	if (envp == NULL)
		return (NULL);
	envp_new = malloc(sizeof(char **) * (get_env_count(envp) + 1));
	if (envp_new == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_new[i] = ft_strdup(envp[i]);
		if (envp_new[i] == NULL)
			return (NULL);
		i++;
	}
	envp_new[i] = NULL;
	return (envp_new);
}
