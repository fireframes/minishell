/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/01 15:41:05 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: what is the use of the following check?
//			if (envp_cpy[i] == NULL)
//				return (NULL);
// ANSWER: ft_strdup allocates new string with malloc,
//			so we have to check if allocation went wrong
char	**copy_envp(char **envp)
{
	char	**envp_cpy;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_cpy = (char **) malloc(sizeof(char *) * (i + 1));
	if (envp_cpy == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		if (envp_cpy[i] == NULL)
			return (NULL);
		i++;
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
}
