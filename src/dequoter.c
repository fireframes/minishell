/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:50:36 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 00:17:53 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static bool	dbl_quotes(char *line, t_quote *quote)
{
	if ((*line) == '\"' && !quote->dbl_quote && !quote->sngl_quote
		&& ft_strchr(line + 1, '\"'))
	{
		quote->dbl_quote = true;
		quote->isquoted = true;
		return (true);
	}
	else if ((*line) == '\"' && quote->dbl_quote && !quote->sngl_quote)
	{
		quote->dbl_quote = false;
		quote->isquoted = false;
		return (true);
	}
	return (false);
}

static bool	dequoter(char *line, t_quote *quote)
{
	if ((*line) == '\'' && !quote->sngl_quote && !quote->dbl_quote
		&& ft_strchr(line + 1, '\''))
	{
		quote->sngl_quote = true;
		quote->isquoted = true;
		return (true);
	}
	else if (*line == '\'' && quote->sngl_quote && !quote->dbl_quote)
	{
		quote->sngl_quote = false;
		quote->isquoted = false;
		return (true);
	}
	else if (dbl_quotes(line, quote))
		return (true);
	return (false);
}

int	is_inquotes(char *line, t_quote *quote, int *inqoutes, int *j)
{
	if (dequoter(line, quote))
		return (1);
	if (quote->isquoted)
		inqoutes[*j] = 1;
	return (0);
}

t_expnd	*dequote_expand(char *read_line, t_env *envp)
{
	t_expnd	*expanded_line;
	t_quote	quote;

	if (!read_line || !envp)
		return (NULL);
	if (ft_strlen(read_line) > PATH_MAX)
	{
		ft_putstr_fd(": input is too long\n", 2);
		return (NULL);
	}
	quote.sngl_quote = false;
	quote.dbl_quote = false;
	quote.isquoted = false;
	expanded_line = expander(read_line, envp, &quote);
	if (!expanded_line || !expanded_line->expanded
		|| expanded_line->expanded[0] == '\0')
	{
		if (expanded_line)
			free_expand(expanded_line);
		return (NULL);
	}
	return (expanded_line);
}
