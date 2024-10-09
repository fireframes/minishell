/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:21 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/09 22:57:39 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*copy_expanded(char expanded[])
{
	char	*copy;

	copy = ft_strdup(expanded);
	if (!copy)
		return (NULL);
	return (copy);
}

char	*expander(char *str, t_env *envp)
{
	char	expanded[PATH_MAX];
	char 	*env_value;
	int		j;
	int		i;

	ft_memset(expanded, '$', PATH_MAX);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!str[i + 1])
			{
				expanded[j] = '$';
				expanded[j + 1] = '\0';
				return (copy_expanded(expanded));
			}
			else if (str[i + 1] == '?')
			{
				expanded[j] = '\0';
				j += mini_strcat(&expanded[j], ft_itoa(envp->exit_code));
				i += 2;
				continue ;
			}
			else if (env_exists(&str[i + 1], *envp->env))
			{
				expanded[j] = '\0';
				env_value = ft_strchr(*env_exists(&str[i + 1], *envp->env), '=');
				j += mini_strcat(&expanded[j], ++env_value);
				i += env_value - *env_exists(&str[i + 1], *envp->env);
				continue ;
			}
			else if (ft_strchr(&str[i + 1], '$'))
			{
				i += ft_strchr(&str[i + 1], '$') - str;
				continue ;
			}
			else
				break ;
		}
		else
			expanded[j] = str[i];
		i++;
		j++;
	}
	expanded[j] = '\0';
	return (copy_expanded(expanded));
}
