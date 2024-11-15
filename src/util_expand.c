/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:09:07 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:22:48 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_expand(t_expd_data *data, char *line, t_env *envp, t_quote *quote)
{
	data->line = line;
	data->envp = envp;
	data->quote = quote;
	data->i = 0;
	data->j = 0;
}

void	process_line(t_expd_data *data)
{
	while (data->line[data->i])
	{
		if (dequoter(&data->line[data->i], data->quote))
		{
			data->i++;
			continue ;
		}
		if (data->quote->isquoted)
			data->inquotes[data->j] = 1;
		if (data->line[data->i] == '$' && !data->quote->sngl_quote)
			handle_dollar_sign(data);
		else
			data->expanded[data->j++] = data->line[data->i++];
	}
	data->expanded[data->j] = '\0';
	data->inquotes[data->j] = -1;
}

void	handle_exit_code(t_expd_data *data)
{
	char	*last_exit_code;

	data->expanded[data->j] = '\0';
	last_exit_code = ft_itoa(data->envp->exit_code);
	if (!last_exit_code)
		return ;
	data->j += mini_strcat(&data->expanded[data->j], last_exit_code);
	data->i += 2;
	free(last_exit_code);
}

void	handle_env_var(t_expd_data *data)
{
	if (env_exists(&data->line[data->i + 1], *data->envp->env))
	{
		data->i += is_expandable_env(&data->line[data->i + 1],
				data->envp, &data->expanded[data->j], &data->j);
		data->i++;
	}
	else
	{
		data->i++;
		while (data->line[data->i]
			&& !ft_strchr(" |<>\"'$", data->line[data->i]))
			data->i++;
	}
}

void	handle_dollar_sign(t_expd_data *data)
{
	if (data->line[data->i + 1] == '\0'
		|| data->line[data->i + 1] == '\"'
		|| data->line[data->i + 1] == ' ')
	{
		data->expanded[data->j++] = '$';
		data->i++;
	}
	else if (data->line[data->i + 1] == '?')
		handle_exit_code(data);
	else
		handle_env_var(data);
}
