/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:21 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/24 16:00:01 by mmaksimo         ###   ########.fr       */
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

int	*init_inquotes(int inquotes[])
{
	int	*inq_arr;
	int	i;

	i = 0;
	while (inquotes[i] != -1)
		i++;
	inq_arr = malloc(sizeof(int) * (i + 1));
	if (!inq_arr)
		return (NULL);
	i = 0;
	while (inquotes[i] != -1)
	{
		inq_arr[i] = inquotes[i];
		i++;
	}
	inq_arr[i] = -1;
	return (inq_arr);
}

static t_expnd	*alloc_expand(char expanded[], int inquotes[])
{
	t_expnd		*expand;

	expand = malloc(sizeof(t_expnd));
	if (!expand)
		return (NULL);
	expand->expanded = ft_strdup(expanded);
	if (!expand->expanded)
	{
		free(expand);
		return (NULL);
	}
	expand->inquotes = init_inquotes(inquotes);
	if (!expand->inquotes)
	{
		free(expand->expanded);
		free(expand);
		return (NULL);
	}
	return (expand);
}
// PROBLEM: line can be any size.
//			need to allocate instead of using fixed-size?
static t_expnd	*expander(char *line, t_env *envp)
{
	char	expanded[PATH_MAX];
	int		inqoutes[PATH_MAX];
	char	*env_value;
	int		j;
	int		i;
	bool	single_quote;
	bool	double_quote;
	bool	isquoted;

	if (!line || ft_strlen(line) > PATH_MAX)
	{
		ft_putstr_fd(": input is too long", 2);
		return (NULL);
	}
	ft_memset(inqoutes, 0, PATH_MAX);
	single_quote = false;
	double_quote = false;
	isquoted = false;
	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i]) == '\'' && !single_quote && !double_quote)
		{
			single_quote = true;
			isquoted = true;
			i++;
			continue ;
		}
		else if (line[i] == '\'' && single_quote && !double_quote)
		{
			single_quote = false;
			isquoted = false;
			i++;
			continue ;
		}
		else if ((line[i]) == '\"' && !double_quote && !single_quote)
		{
			double_quote = true;
			isquoted = true;
			i++;
			continue ;
		}
		else if ((line[i]) == '\"' && double_quote && !single_quote)
		{
			double_quote = false;
			isquoted = false;
			i++;
			continue ;
		}
		if (isquoted)
			inqoutes[j] = 1;
		if (line[i] == '$' && !single_quote)
		{
			if (line[i + 1] == '\0' || line[i + 1] == '\"')
				expanded[j] = '$';
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
			else if (!env_exists(&line[i + 1], *envp->env))
			{
				expanded[j] = ' ';
				char *end;

				end = &line[i];

				if (ft_strchr(&line[i], ' '))
					end = ft_strchr(&line[i], ' ');
				else if (ft_strchr(&line[i + 1], '|'))
					end = ft_strchr(&line[i + 1], '|');
				else if (ft_strchr(&line[i + 1], '<'))
					end = ft_strchr(&line[i + 1], '<');
				else if (ft_strchr(&line[i + 1], '>'))
					end = ft_strchr(&line[i + 1], '>');
				else
				{
					while (*end)
						end++;
				}
				j += end - &line[i] - 1;
				// printf("j is : %d\n", j);
				// inqoutes[j] = -1;
				// return (alloc_expand(expanded, inqoutes));
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
	inqoutes[j] = -1;
	return (alloc_expand(expanded, inqoutes));
}


t_expnd	*dequote_expand(char *read_line, t_env *envp)
{
	t_expnd	*expanded_line;

	expanded_line = expander(read_line, envp);
	if (!expanded_line)
		return (NULL);
	return (expanded_line);
}
