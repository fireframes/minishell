/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:21:21 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:23:27 by mmaksimo         ###   ########.fr       */
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

int	is_expandable_env(char *line_ptr, t_env *envp, char *expanded, int *j)
{
	char	*env_value;
	char	*env_entry;

	env_value = NULL;
	*expanded = '\0';
	env_entry = *env_exists(line_ptr, *envp->env);
	if (!env_entry)
		return (0);
	env_value = ft_strchr(env_entry, '=');
	if (!env_value)
		return (0);
	*j += mini_strcat(expanded, ++env_value);
	return (env_value - env_entry);
}

t_expnd	*expander(char *line, t_env *envp, t_quote *quote)
{
	t_expd_data		data;
	char			expanded[PATH_MAX];
	int				inquotes[PATH_MAX];

	if (!line || !envp || !quote)
		return (NULL);
	ft_memset(inquotes, 0, PATH_MAX);
	data.expanded = expanded;
	data.inquotes = inquotes;
	init_expand(&data, line, envp, quote);
	process_line(&data);
	return (alloc_expand(expanded, inquotes));
}
