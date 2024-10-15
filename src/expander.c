/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:21 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/15 20:43:09 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mini_strcat(char *dest, const char *src)
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

static char	*copy_expanded(char expanded[])
{
	char	*copy;

	copy = ft_strdup(expanded);
	if (!copy)
		return (NULL);
	return (copy);
}

// static int	check_quotes(char c)
// {
// 	if (c == '\"' || c == '\'')
// 		return (1);
// 	return (0);
// }

// char*	quoter(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if ((line[i]) == '\'' && !single_quote && !double_quote)
// 		{
// 			single_quote = true;
// 			i++;
// 			continue ;
// 		}
// 		else if (line[i] == '\'' && single_quote)
// 		{
// 			single_quote = false;
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i]) == '\"' && !double_quote)
// 		{
// 			double_quote = true;
// 			i++;
// 			continue ;
// 		}
// 		else if ((line[i]) == '\"' && double_quote)
// 		{
// 			double_quote = false;
// 			i++;
// 			continue ;
// 		}
// 	}
// }

char	*expander(char *line, t_env *envp)
{
	char	expanded[PATH_MAX];
	char	*env_value;
	int		j;
	int		i;
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i]) == '\'' && !single_quote)
		{
			single_quote = true;
			i++;
			continue ;
		}
		else if (line[i] == '\'' && single_quote)
		{
			single_quote = false;
			i++;
			continue ;
		}
		if ((line[i]) == '\"' && !double_quote)
		{
			double_quote = true;
			i++;
			continue ;
		}
		else if ((line[i]) == '\"' && double_quote)
		{
			double_quote = false;
			i++;
			continue ;
		}
		if (line[i] == '$' && !single_quote)
		{
			if (line[i + 1] == '\0' || line[i + 1] == '\"')
			{
				expanded[j] = '$';
				// expanded[j + 1] = '\0';
				// return (copy_expanded(expanded));
			}
			else if (line[i + 1] == '?')
			{
				expanded[j] = '\0';
				j += mini_strcat(&expanded[j], ft_itoa(envp->exit_code));
				i += 2;
				continue ;
			}
			else if (env_exists(&line[i + 1], *envp->env))
			{
				expanded[j] = '\0';
				env_value = ft_strchr(*env_exists(&line[i + 1], *envp->env), '=');
				j += mini_strcat(&expanded[j], ++env_value);
				i += env_value - *env_exists(&line[i + 1], *envp->env);
				continue ;
			}
			else if (ft_strchr(&line[i + 1], '$'))
			{
				i += ft_strchr(&line[i + 1], '$') - line;
				continue ;
			}
			else
				break ;
		}
		else
			expanded[j] = line[i];
		i++;
		j++;
	}
	expanded[j] = '\0';
	return (copy_expanded(expanded));
}

char	*dequote_expand(char *read_line, t_env *envp)
{
	char	*expanded_line;

	expanded_line = NULL;
	if (ft_strchr(read_line, '$') || ft_strchr(read_line, '\'')
		|| ft_strchr(read_line, '\"'))
	{
		expanded_line = expander(read_line, envp);
		if (!expanded_line)
			return (NULL);
	}
	return (expanded_line);
}
