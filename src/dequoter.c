/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequoter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:50:36 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/15 18:56:05 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *dequoter(char *line)
{
	int		i;
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;

	i = 0;
	while(line[i])
	{
		if ((line[i]) == '\'' && !single_quote && !double_quote)
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
	}
	return (NULL);
}
