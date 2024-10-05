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

// QUESTION: the function is almost the same as copy_envp. maybe do it with one?
int	add_env(char *arg, t_env *envp)
{
	char	**envp_old;
	char	**envp_new;
	int		i;

	envp_old = envp->env[envp->real_shlvl];
	envp_new = malloc(sizeof(char **) * (get_env_count(envp_old) + 2));
	if (envp_new == NULL)
		return (-1);
	i = 0;
	while (envp_old[i] != NULL)
	{
		envp_new[i] = ft_strdup(envp_old[i]);
		if (envp_new[i] == NULL)
			return (-1);
		i++;
	}
	envp_new[i] = ft_strdup(arg);
	if (envp_new[i] == NULL)
		return (-1);
	envp_new[i + 1] = NULL;
	envp->env[envp->real_shlvl] = envp_new;
	free_arr_of_arr(envp_old);
	return (0);
}

size_t	get_envvar_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}
// Compares envvar from arg to envvar from envp
// QUESTION: could we use getenv() here?
char	**env_exists(char *arg, char **envp)
{
	int		i;
	size_t	env1_len;
	size_t	env2_len;

	env1_len = get_envvar_len(arg);
	env2_len = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		env2_len = get_envvar_len(envp[i]);
		if(ft_strncmp(arg, envp[i], env1_len) == 0 && env1_len == env2_len)
			return (&envp[i]);
		i++;
	}
	return (NULL);
}


