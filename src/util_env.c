/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/14 17:11:40 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_count(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

char	**copy_env(char **envp)
{
	char	**envp_new;
	int		i;

	if (envp == NULL)
		return (NULL);
	envp_new = malloc(sizeof(char *) * (get_env_count(envp) + 1));
	if (envp_new == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_new[i] = ft_strdup(envp[i]);
		if (envp_new[i] == NULL)
		{
			while (i-- > 0)
				free(envp_new[i]);
			free(envp_new);
			return (NULL);
		}
		i++;
	}
	envp_new[i] = NULL;
	return (envp_new);
}

size_t	get_env_len(char *str)
{
	size_t	i;
	size_t	str_len;

	if (!str)
		return (0);
	i = 0;
	str_len = ft_strlen(str);
	while (i < str_len)
	{
		if (str[i] == '=' || str[i] == '$'
			|| str[i] == ' ' || str[i] == '\"')
			break ;
		i++;
	}
	return (i);
}

char	**env_exists(char *arg, char **envp)
{
	int		i;
	size_t	env1_len;
	size_t	env2_len;

	env1_len = get_env_len(arg);
	env2_len = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		env2_len = get_env_len(envp[i]);
		if (ft_strncmp(arg, envp[i], env1_len) == 0 && env1_len == env2_len)
			return (&envp[i]);
		i++;
	}
	return (NULL);
}

bool	isvalid_arg(char *arg)
{
	char	*arg_tmp;

	if (*arg == '=')
	{
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (false);
	}
	arg_tmp = arg;
	if (!(ft_isalpha(*arg_tmp) || *arg_tmp == '_'))
	{
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (false);
	}
	arg_tmp++;
	while (*arg_tmp != '=' && *arg_tmp)
	{
		if (!(ft_isalnum(*arg_tmp) || *arg_tmp == '_'))
		{
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (false);
		}
		arg_tmp++;
	}
	return (true);
}
