/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/15 15:19:45 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**cmds_parse(char *read_line)
{
	char		**cmds_splits;

	cmds_splits = NULL;
	cmds_splits = split_v2(read_line, '|');
	return (cmds_splits);
}

static void	check_for_minishell_call(t_cmd *cmd_struc, char *arg, int i)
{
	if (ft_strnstr(arg, "/minishell", ft_strlen(arg)) != NULL)
		cmd_struc[i].minishell_call = true;
}

// TODO wrap the if(...) into command_error()
// TODO take into account relative and absolute commands paths too!
// BIG PARSING MODULE!
// Parsing just before the split call?
// 'free_split(commands->cmds_split)' has been deleted the line before printf
// TODO problem with double free when trying an unexisting command
// If you unset PATH, you have this message:
//		bash: ls: No such file or directory
//	(not the command not found)
static void	cmd_args_parse(t_cmd *cmds_struc, t_env *envp)
{
	int	i;

	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		cmds_struc[i].command_index = i;
		cmds_struc[i].args = split_v2(cmds_struc->cmds_splits[i], ' ');
		expand_cmd(cmds_struc[i].args, envp);
		if (cmds_struc[i].redir_syntax_err == true)
		{
			i++;
			continue ;
		}
		else if (check_builtin(&cmds_struc[i]))
			cmds_struc[i].is_builtin = true;
		else
		{
			cmds_struc[i].cmd_path = find_cmd_path(cmds_struc[i].args[0], envp->env[envp->real_shlvl]);
			if (!cmds_struc[i].cmd_path)
			{
				ft_putstr_fd(cmds_struc[i].args[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				cmds_struc[i].path_found = false;
			}
			else
			{
				cmds_struc[i].path_found = true;
				check_for_minishell_call(cmds_struc, cmds_struc[i].args[0], i);
			}
		}
		i++;
	}
}

static void	count_args(t_cmd *cmds_struc)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		j = 0;
		while (cmds_struc[i].args[j] != NULL)
			j++;
		cmds_struc[i].total_args = j;
		i++;
	}
}

// TODO: PARSING FOR QUOTES SHOULD HAPPEN before the call of cmds_parse()
// TO YANNICK: are you sure about the above assumption?

// PROBLEM: cmd[0] at this point is first validated in parsing module
// 			and isn't expanded when checked for command existance
// FIX:		added expansion to cmd_args_parse()
//			but need to add error code before expanding somehow
t_cmd	*parsing_module(t_env *envp, char *read_line, t_cmd *cmds_struc)
{
	char		**cmds_splits;

	cmds_splits = NULL;
	cmds_splits = cmds_parse(read_line);
	cmds_struc = create_cmds_struc(cmds_splits, cmds_struc);
	redir_parsing_module(cmds_struc);
	cmd_args_parse(cmds_struc, envp);
	// expand_cmds(cmds_struc, envp);
	count_args(cmds_struc);
	return (cmds_struc);
}
