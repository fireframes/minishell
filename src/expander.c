/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:21 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/31 18:03:52 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_expandable_env(char *line_ptr, t_env *envp, char *expanded, int *j)
{
	char	*env_value;

	env_value = NULL;
	*expanded = '\0';
	env_value = ft_strchr(*env_exists(line_ptr, *envp->env), '=');
	*j += mini_strcat(expanded, ++env_value);
	return (env_value - *env_exists(line_ptr, *envp->env));
}

bool	non_expandable_env(char *line, int *index, t_env *envp)
{
	int	offset;

	offset = 0;
	if (!env_exists(&line[*index + 1], *envp->env))
	{
		if (ft_strchr(&line[*index], ' '))
			offset = ft_strchr(&line[*index], ' ') - line;
		else if (ft_strchr(&line[*index + 1], '|'))
			offset = ft_strchr(&line[*index + 1], '|') - line;
		else if (ft_strchr(&line[*index + 1], '<'))
			offset = ft_strchr(&line[*index + 1], '<') - line;
		else if (ft_strchr(&line[*index + 1], '>'))
			offset = ft_strchr(&line[*index + 1], '>') - line;
		else
		{
			while (line[offset])
				offset++;
		}
		*index += offset;
		return (true);
	}
	return (false);
}

// PROBLEM: line can be any size.
//			need to allocate instead of using fixed-size?
static t_expnd	*expander(char *line, t_env *envp, t_quote *quote)
{
	char	expanded[PATH_MAX];
	int		inqoutes[PATH_MAX];
	int		j;
	int		i;

	ft_memset(inqoutes, 0, PATH_MAX);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (dequoter(&line[i], quote))
		{
			i++;
			continue ;
		}
		if (quote->isquoted)
			inqoutes[j] = 1;
		if (line[i] == '$' && !quote->sngl_quote)
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
				i += is_expandable_env(&line[i + 1], envp, &expanded[j], &j);
				continue ;
			}
			else if (non_expandable_env(&line[i + 1], &i, envp))
				expanded[j] = ' ';
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
	// if (quote->isquoted)
	// 	ft_memset(inqoutes, 0, PATH_MAX);
	expanded[j] = '\0';
	inqoutes[j] = -1;
	return (alloc_expand(expanded, inqoutes));
}

t_expnd	*dequote_expand(char *read_line, t_env *envp)
{
	t_expnd	*expanded_line;
	t_quote	quote;

	if (!read_line || ft_strlen(read_line) > PATH_MAX)
	{
		ft_putstr_fd(": input is too long\n", 2);
		return (NULL);
	}
	quote.sngl_quote = false;
	quote.dbl_quote = false;
	quote.isquoted = false;
	expanded_line = expander(read_line, envp, &quote);
	if (!expanded_line)
		return (NULL);
	return (expanded_line);
}
