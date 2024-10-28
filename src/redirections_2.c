/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/23 15:49:26 by mmaksimo         ###   ########.fr       */
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
		l++;
		c[i].redirs[j][l] = '>';
		l++;
		k = k + 2;
	}
	else if (c[i].redir_part[k] == '<' && c[i].redir_part[k + 1] == '<')
	{
		c[i].redirs[j][l] = '<';
		l++;
		c[i].redirs[j][l] = '<';
		l++;
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
	while (c[i].redir_part[k] == ' ')
		k++;
	while (c[i].redir_part[k] != '<' && c[i].redir_part[k] != '>'
		&& c[i].redir_part[k] != '\0' && c[i].redir_part[k] != ' ')
	{
		c[i].redirs[j][l] = c[i].redir_part[k];
		l++;
		k++;
	}
	c[i].redirs[j][l] = '\0';
	// l = 0;
	// while (c[i].cmds_splits[i][l] != '\0')
	// 	l++;
	// c[i].cmds_splits[i][l] = ' ';
	while (c[i].redir_part[k] != '<' && c[i].redir_part[k] != '>'
		&& c[i].redir_part[k] != '\0')
	{
		// c[i].cmds_splits[i][l] = c[i].redir_part[k];
		// l++;
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

static int	find_1st_redir_type(char *str, int *inquotes)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && !inquotes[i])
			return (1);
		if (str[i] == '>' && !inquotes[i])
			return (2);
		i++;
	}
	return (0);
}

void	isolate_redir_part(t_cmd *cmds_struc, int *inquotes)
{
	int		i;
	int		inq_offset;
	char	*first_redir_found;
	// char	*first_space_char;

	i = 0;
	inq_offset = 0;
	while (i < cmds_struc->total_cmds)
	{
		first_redir_found = NULL;
		if (find_1st_redir_type(cmds_struc[i].cmds_splits[i], &inquotes[inq_offset]) == 1)
			first_redir_found = ft_strchr(cmds_struc[i].cmds_splits[i], '<');
		if (find_1st_redir_type(cmds_struc[i].cmds_splits[i], &inquotes[inq_offset]) == 2)
			first_redir_found = ft_strchr(cmds_struc[i].cmds_splits[i], '>');
		inq_offset += ft_strlen(cmds_struc->cmds_splits[i]) + 1;
		if (first_redir_found != NULL)
		{
			cmds_struc[i].redir_part = ft_strdup(first_redir_found);
			while (*first_redir_found != '\0')
			{
				*first_redir_found = '\0';
				first_redir_found++;
			}
		}
		i++;
	}
}
