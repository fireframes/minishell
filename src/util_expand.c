/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:38:36 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 00:27:31 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_expandable(char *line_ptr, t_env *envp, char *expanded, int *j)
{
	char	*env_value;

	env_value = NULL;
	*expanded = '\0';
	env_value = ft_strchr(*env_exists(line_ptr, *envp->env), '=');
	*j += mini_strcat(expanded, ++env_value);
	return (env_value - *env_exists(line_ptr, *envp->env));
}

int	handle_dollar(char *line, int i, char *expanded, int *j, t_env *envp)
{
	if (line[i + 1] == '\0' || line[i + 1] == '\"')
		expanded[*j] = '$';
	else if (line[i + 1] == '?')
	{
		expanded[*j] = '\0';
		char *last_exit_code = ft_itoa(envp->exit_code);
		if (!last_exit_code)
			return (-1);
		*j += mini_strcat(&expanded[*j], last_exit_code);
		free(last_exit_code);
		return (2);
	}
	else if (env_exists(&line[i + 1], *envp->env))
		return (is_expandable(&line[i + 1], envp, &expanded[*j], j));
	else if (ft_strchr(&line[i + 1], '$'))
		return (ft_strchr(&line[i + 1], '$') - line);
	else
	{
		i++;
		while (line[i] && !ft_strchr(" |<>\"'$", line[i]))
			i++;
		return (i - (i - 1));
	}
	return (0);
}
