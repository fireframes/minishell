/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/20 19:17:12 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"

typedef struct	s_command
{
	char	**cmds_split;
	int		total_cmds;
	char	**args;
	char	*cmd_path;
	int		command_index;
	bool	is_builtin;
	bool	path_found;
}	t_command;

// checker.c
bool	check_builtin(t_command *command);

// parser.c
// ...

// util_split.c:
char	**split_v2(char const *s, char c);

// util_path.c:
char	*find_command_path(char *command, char **envp, char **cmd_flags);

// util_strjoin.c:
char	*strnstr_v2(const char *haystack, const char *needle, size_t len);
char	*strjoin_v2(char const *s1, char const *s2);

// built-ins
int		ft_echo(t_command *cmd);

// execution.c
void	execute_builtin(t_command *cmd);

#endif
