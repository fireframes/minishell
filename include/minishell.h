/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 01:29:21 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include "linux/limits.h"
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
//  - cmds_splits, the adress of a MALLOCATED array of array of chars contained
//		at least one command attempts as a string (copied into each sub-struct);
//  - total_cmds, an integer for the number of commands (existing or not, with
//		or without flags) separated by pipe(s). If no pipes (and at least one
//		character), equals to 1 (copied into each sub-structure);
//  - args, the adress of a MALLOCATED array of array of chars for the arguments
// 		contained in a given command, separated by 1 space char, which could
// 		be flags, path, other arguments or parameters (path, etc.). It contains
// 		at least the same thing as cmds_splits, if no other arguments (each sub-
//		contains its own;
//  - cmd_path, the adress of a MALLOCATED string of chars containing the path
//		of the command, OR NULL if non (each sub-structure has its own value);
//  - command_index, an integer starting at 0 to keep trace of the index of the
//		commands (each sub-structure has its own value);
//  - is_builtin, a boolean saying if the command exact name (string) is the
//		same as one of the 8 built-ins (plus 1 with flag). Each sub-structure
//		has its own value;
//  - (*pipes)[2], an array of 2 integers [...] [...]
//	- path_found, a boolean saying if a path has been found for the command. 
// 		Each sub-structure has its own value. [NB: is that really needed, 
//		because normally if no path has been found, the cmd_path string should 
//		be NULL?]
//	- pid, [...] [...]
//	- read_fd, an integer [...] [...]
//	- write_fd, an integer [...] [...]
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
bool		check_builtin(t_command *command);

// parsing.c
t_command	*parsing_module(char **envp, char *read_line, t_command *commands);
char		**cmds_parse(char *read_line);
void		cmd_args_parse(t_command *commands, char **envp);

// freeing.c
void		free_module(t_command *cmds_struc, char *read_l, char *prompt_path);
void		free_arr_of_arr(char **split);
void		free_structs(t_command *commands);

// fork_and_processes.c
void		exec_cmd(t_command cmd, int read_fd, int write_fd, char **envp);
void		init_pipes(t_command *commands);
void		parent_process(t_command *commands);
void		child_process(t_command *commands, int i, char **envp);
void		forking(t_command *commands, char **envp);

// util_split.c:
char		**split_v2(char const *s, char c);

// util_path.c:
char		*find_cmd_path(char *command, char **envp);

// util_strjoin.c:
char		*strnstr_v2(const char *haystack, const char *needle, size_t len);
char		*strjoin_v2(char const *s1, char const *s2);

// built-ins
int			ft_echo(t_command *cmd);
int			ft_cd(t_command *cmd);
int			ft_pwd(t_command *cmd);

int			ft_env(t_command *cmd, char **env);

// execution.c
void		execution_module(t_command *commands, char**envp);
void		execute_builtin(t_command *cmd, char **env);

//minishell.c
t_command	*create_struct(char **cmds_splits, t_command *commands);

#endif
