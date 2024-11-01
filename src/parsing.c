/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/01 16:17:21 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_for_minishell_call(t_cmd *cmd_struc, char *arg, int i)
{
	if (ft_strnstr(arg, "/minishell", ft_strlen(arg)) != NULL)
		cmd_struc[i].minishell_call = true;
}

static void	deal_with_path(t_cmd *cm, t_env *envp, int i)
{
	cm[i].cmd_path = find_cmd_path(cm[i].args[0], envp->env[envp->real_shlvl]);
	if (!cm[i].cmd_path)
	{
		ft_putstr_fd(cm[i].args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cm[i].path_found = false;
	}
	else
	{
		cm[i].path_found = true;
		check_for_minishell_call(cm, cm[i].args[0], i);
	}
}

static void	cmd_args_parse(t_cmd *cm, t_env *envp, int *inquotes)
{
	int		i;
	size_t	inq_offset;

	i = 0;
	inq_offset = 0;
	while (cm != NULL && (i < cm->total_cmds))
	{
		cm[i].command_index = i;
		cm[i].args = split_v3(cm->cmds_splits[i], ' ', &inquotes[inq_offset]);
		inq_offset += ft_strlen(cm->cmds_splits[i]) + 1;
		if (cm[i].redir_part)
			inq_offset += ft_strlen(cm[i].redir_part);
		if (cm[i].redir_syntax_err == true || cm[i].args == NULL)
		{
			i++;
			continue ;
		}
		else if (check_builtin(&cm[i]))
			cm[i].is_builtin = true;
		else
			deal_with_path(cm, envp, i);
		i++;
	}
}

static void	count_args(t_cmd *cmds_struc)
{
	int	i;
	int	j;

	i = 0;
	while (cmds_struc != NULL && (i < cmds_struc->total_cmds))
	{
		if (cmds_struc[i].args != NULL)
		{
			j = 0;
			while (cmds_struc[i].args[j] != NULL)
				j++;
			cmds_struc[i].total_args = j;
		}
		i++;
	}
}

t_cmd	*parsing_module(t_env *envp, char *read_line, t_cmd *cmds_struc)
{
	char		**cmds_splits;
	t_expnd		*expand;

	envp->redir_syntax_err = false;
	envp->total_heredocs_in_all = 0;
	cmds_splits = NULL;
	expand = dequote_expand(read_line, envp);
	if (!expand)
		return (NULL);
	cmds_splits = cmds_parse(expand->expanded, expand->inquotes);
	if (!cmds_splits)
	{
		free_expand(expand);
		return (NULL);
	}
	cmds_struc = create_cmds_struc(cmds_splits, cmds_struc, envp);
	redir_parsing_module(cmds_struc, envp, expand->inquotes);
	cmd_args_parse(cmds_struc, envp, expand->inquotes);
	count_args(cmds_struc);
	free_expand(expand);
	return (cmds_struc);
}
