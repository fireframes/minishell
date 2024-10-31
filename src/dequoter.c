/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:50:36 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/31 11:30:00 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	dbl_quotes(char *line, t_quote *quote)
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

bool	dequoter(char *line, t_quote *quote)
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
