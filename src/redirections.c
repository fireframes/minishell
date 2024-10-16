/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/09 12:04:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_a_redir(char *arg)
{
    if (strncmp_v2(arg, ">>", 2) == 0)
        return (2);
	else if (strncmp_v2(arg, ">", 1) == 0 || strncmp_v2(arg, "<", 1) == 0)
		return (1);
    else
        return (0);
}

static void	count_redirections(t_cmd *cmds_struc, int i)
{
    int j;

    j = 0;
    while (cmds_struc[i].redir_part[j] != '\0')
	{
		if (is_a_redir(&cmds_struc[i].redir_part[j]) == 2)
		{
			cmds_struc[i].redir_amount++;
			j = j + 2;
		}
		else
		{
			if (is_a_redir(&cmds_struc[i].redir_part[j]) == 1)
				cmds_struc[i].redir_amount++;
		j++;
		}
	}
	i++;
}

static bool	erroneous_next_c(t_cmd *c, int i, int j)
{
	if (c[i].redir_part[j + 1] == '\0')
		return (true);
	if (c[i].redir_part[j + 1] == '>')
		return (true);
	if (c[i].redir_part[j + 1] == '<')
		return (true);
	while (c[i].redir_part[j + 1] != '\0')
	{
		if (c[i].redir_part[j + 1] != ' ' && c[i].redir_part[j + 1] != '\t')
			return (false);
		j++;
	}
	return (true);
}

static bool	is_syntax_err(t_cmd *c, int i)
{
	int	j;

	j = 0;
	while (c[i].redir_part != NULL && c[i].redir_part[j] != '\0')
	{
		if (c[i].redir_part[j] == '<')
		{
			if (erroneous_next_c(c, i, j) == true)
				return (true);
		}
		else if (c[i].redir_part[j] == '>')
		{
			if (c[i].redir_part[j + 1] == '>')
				j++;
			if (erroneous_next_c(c, i, j) == true)
				return (true);
		}
		j++;
	}
	return (false);
}

static void	isolate_redir_part(t_cmd *cmds_struc)
{
	int		i;
	char	*first_redir_found;

	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		first_redir_found = 0;
		first_redir_found = ft_strchr(cmds_struc[i].cmds_splits[i], '>');
		if (first_redir_found == NULL)
			first_redir_found = ft_strchr(cmds_struc[i].cmds_splits[i], '<');
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

void	redir_parsing_module(t_cmd *cmds_struc, t_env *envp)
{
	int	i;

	i = 0;
	isolate_redir_part(cmds_struc);
	while (i < cmds_struc->total_cmds)
	{
		if (is_syntax_err(cmds_struc, i) == true)
		{
			cmds_struc[i].redir_syntax_err = true;
			envp->redir_syntax_err = true;
		}
		else if (cmds_struc[i].redir_part != NULL)
			count_redirections(cmds_struc, i);
		i++;
	}
}
