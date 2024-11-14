/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:21 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 00:28:26 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_expnd	*alloc_expand(char expanded[], int inquotes[])
{
	t_expnd	*expand;

	if (!expanded || expanded[0] == '\0')
		return (NULL);
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

t_expnd	*expander(char *line, t_env *envp, t_quote *quote)
{
	char	expanded[PATH_MAX];
	int		inqoutes[PATH_MAX];
	int		j;
	int		i;

	if (!line || !envp || !quote)
		return (NULL);
	ft_memset(inqoutes, 0, PATH_MAX);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_inquotes(&line[i], quote, inqoutes, &j))
		{
			i++;
			continue ;
		}
		if (line[i] == '$' && !quote->sngl_quote)
		{
			int	skip = handle_dollar(line, i, expanded, &j, envp);
			if (skip < 0)
				return (NULL);
			i += skip;
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
