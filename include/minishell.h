/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/24 17:35:48 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
#include "linux/limits.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"

// The following structure is generally accessed as an array of structures
// It contains the following elements:
//  -
//  -
//  -
//  -
//  -
//  -
//  -
// QUESTION: can (*pipes)[2] (defined in init_pipes) could only be pipes here?
// IMPORTANT: some of the struct var are accessed in the struct, other in an
//	array of that struct!
typedef struct s_command
{
	char	**cmds_splits;
	int		total_cmds;
	char	**args;
	char	*cmd_path;
	int		command_index;
	bool	is_builtin;
	bool	path_found;
	int		(*pipes)[2];
	pid_t	pid;
	int		read_fd;
	int		write_fd;
}	t_command;

// checker.c
bool	check_builtin(t_command *command);

// parsing.c
void	cmds_parse(t_command *commands, char **envp);

// freeing.c
void	free_split(char **split);
void	free_commands(t_command *commands, int cmd_cnt);

// fork_and_processes.c
void	exec_cmd(t_command cmd, int read_fd, int write_fd, char **envp);
void	init_pipes(t_command *commands);
void	parent_process(t_command *commands);
void	child_process(t_command *commands, int i, char **envp);
void	forking(t_command *commands, char **envp);

// util_split.c:
char	**split_v2(char const *s, char c);

// util_path.c:
char	*find_command_path(char *command, char **envp, char **cmd_flags);

// util_strjoin.c:
char	*strnstr_v2(const char *haystack, const char *needle, size_t len);
char	*strjoin_v2(char const *s1, char const *s2);

// built-ins
int		ft_echo(t_command *cmd);
int		ft_cd(t_command *cmd);
int		ft_pwd(t_command *cmd);

// execution.c
void	execute_builtin(t_command *cmd);

#endif
