/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/11 20:38:42 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool erroneous_next_c(t_cmd *c, int i, int j)
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

static bool is_syntax_err(t_cmd *c)
{
	int i;
	int j;

	i = 0;
	while (i < c->total_cmds)
	{
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
		i++;
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
			cmds_struc->redir_part = ft_strdup(first_redir_found);
			while (*first_redir_found != '\0')
			{
				*first_redir_found = '\0';
				first_redir_found++;
			}
		}
		i++;
	}
}

void	redir_parsing_module(t_cmd *cmds_struc)
{
	isolate_redir_part(cmds_struc);
	if (is_syntax_err(cmds_struc) == true)
		cmds_struc->redir_syntax_err = true;
}

// static bool is_a_redir(char *arg)
// {
//     if (strncmp_v2(arg, ">", 1) == 0 || strncmp_v2(arg, ">>", 2) == 0
//         || strncmp_v2(arg, "<", 1) == 0)
//     {
//         return (true);
//     }
//     else
//         return (false);
// }

// void    count_redirections(t_cmd *cmds_struc)
// {
//     int i;
//     int j;

//     i = 0;
//     count_args(cmds_struc);
//     while (i < cmds_struc->total_cmds)
//     {
//         j = 0;
//         while (j < cmds_struc[i].total_args)
//         {
//             if (is_a_redir(cmds_struc[i].args[j]) == true)
//                 cmds_struc[i].redir_amount++;
//             j++;
//         }
//         i++;
//     }
// }
