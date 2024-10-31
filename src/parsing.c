/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/31 13:12:12 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// move inquotes init to a normal place
static char	**cmds_parse(char *read_line, int *inquotes)
{
	char	**cmds_splits;

	cmds_splits = NULL;
	cmds_splits = split_v3(read_line, '|', inquotes);
	if (!cmds_splits)
		return (NULL);
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
// + 1 for already skipped delimiters
static void	cmd_args_parse(t_cmd *cmds_struc, t_env *envp, int *inquotes)//, int redir_offset)
{
	int	i;
	size_t	inq_offset;

	i = 0;
	inq_offset = 0;
	while (i < cmds_struc->total_cmds)
	{
		cmds_struc[i].command_index = i;
		cmds_struc[i].args = split_v3(cmds_struc->cmds_splits[i], ' ', &inquotes[inq_offset]);
		inq_offset += ft_strlen(cmds_struc->cmds_splits[i]) + 1;
		if (cmds_struc[i].redir_part)
			inq_offset += ft_strlen(cmds_struc[i].redir_part);
		if (cmds_struc[i].redir_syntax_err == true || cmds_struc[i].args == NULL)
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

// PROBLEM: for input like: "$EMPTY" must do nothing with exit code 0
// LACKS ERROR CHECKS
// PROBLEM: SEGFAULT WHEN INPUTTING only "" or """ in the prompt (in that
//	case cmd_struc is still NULL / empty)
t_cmd	*parsing_module(t_env *envp, char *read_line, t_cmd *cmds_struc)
{
	char		**cmds_splits;
	t_expnd		*expand;
	int 		redir_offset;

	envp->redir_syntax_err = false;
	envp->total_heredocs_in_all = 0;
	cmds_splits = NULL;
	expand = dequote_expand(read_line, envp);
	if (!expand)
		return (NULL);
	cmds_splits = cmds_parse(expand->expanded, expand->inquotes);
	//if (!cmds_splits)
	cmds_struc = create_cmds_struc(cmds_splits, cmds_struc, envp);
	//if (!cmds_struc)
	redir_offset = redir_parsing_module(cmds_struc, envp, expand->inquotes);
	(void) redir_offset;
	// printf("redir_offset: %d\n", redir_offset);
	cmd_args_parse(cmds_struc, envp, expand->inquotes);//, redir_offset);
	count_args(cmds_struc);
	free_expand(expand);
	return (cmds_struc);
}
