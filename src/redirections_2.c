/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/31 14:39:37 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_redir(char *str, int *inquotes)
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
	int		offset;
	char	*first_redir_found;

	i = 0;
	offset = 0;
	while (cmds_struc != NULL && i < cmds_struc->total_cmds)
	{
		first_redir_found = NULL;
		if (find_redir(cmds_struc[i].cmds_splits[i], &inquotes[offset]) == 1)
			first_redir_found = ft_strchr(cmds_struc[i].cmds_splits[i], '<');
		if (find_redir(cmds_struc[i].cmds_splits[i], &inquotes[offset]) == 2)
			first_redir_found = ft_strchr(cmds_struc[i].cmds_splits[i], '>');
		if (first_redir_found != NULL)
		{
			cmds_struc[i].redir_part = ft_strdup(first_redir_found);
			while (*first_redir_found != '\0')
			{
				*first_redir_found = '\0';
				first_redir_found++;
			}
		}
		offset += ft_strlen(cmds_struc->cmds_splits[i]) + 1;
		i++;
	}
}
