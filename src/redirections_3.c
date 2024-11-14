/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/14 21:14:06 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_redir_sign(t_cmd *c, int i, int j, int k)
{
	int	l;

	l = 0;
	if (c[i].redir_part[k] == '>' && c[i].redir_part[k + 1] == '>')
	{
		c[i].redirs[j][l] = '>';
		c[i].redirs[j][l + 1] = '>';
		l = l + 2;
		k = k + 2;
	}
	else if (c[i].redir_part[k] == '<' && c[i].redir_part[k + 1] == '<')
	{
		c[i].redirs[j][l] = '<';
		c[i].redirs[j][l + 1] = '<';
		l = l + 2;
		k = k + 2;
	}
	else
	{
		c[i].redirs[j][l] = c[i].redir_part[k];
		l++;
		k++;
	}
	c[i].redirs[j][l] = '\0';
	return (k);
}

static int	copy_filename(t_cmd *c, int i, int j, int k)
{
	int	l;

	l = 0;
	while (c[i].redir_part[k] == ' ' || c[i].redir_part[k] == '\t')
		k++;
	while (c[i].redir_part[k] != '<' && c[i].redir_part[k] != '>'
		&& c[i].redir_part[k] != '\0' && c[i].redir_part[k] != ' ')
	{
		c[i].redirs[j][l] = c[i].redir_part[k];
		l++;
		k++;
	}
	c[i].redirs[j][l] = '\0';
	l = 0;
	while (c[i].cmds_splits[i][l] != '\0')
		l++;
	c[i].cmds_splits[i][l] = ' ';
	while (c[i].redir_part[k] != '<' && c[i].redir_part[k] != '>'
		&& c[i].redir_part[k] != '\0')
	{
		c[i].cmds_splits[i][l] = c[i].redir_part[k];
		l++;
		k++;
	}
	return (k);
}

void	alloc_redir_arr(t_cmd *c, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	c[i].redirs = malloc(sizeof(char **) * (c[i].redir_amount * 2 + 1));
	while (j < (c[i].redir_amount * 2))
	{
		c[i].redirs[j] = malloc(ft_strlen(c[i].redir_part) + 1);
		if (j % 2 == 0)
			k = copy_redir_sign(c, i, j, k);
		else
			k = copy_filename(c, i, j, k);
		j++;
	}
	c[i].redirs[j] = NULL;
}

int	handle_builtin_redirections(t_cmd *cmd)
{
	int	original_stdout;
	int	original_stdin;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	if (cmd && cmd->redirs)
	{
		if (apply_redirections(cmd->redirs) < 0)
		{
			close(original_stdout);
			close(original_stdin);
			return (1);
		}
	}
	return (0);
}
