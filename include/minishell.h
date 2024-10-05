/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/04 20:37:55 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_SHLVL 256

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
typedef struct s_cmd
{
	char	**cmds_splits;
	int		total_cmds;
	char	**args;
	char	*cmd_path;
	int		command_index;
	bool	is_builtin;
	bool	path_found;
	bool	minishell_call;
	int		(*pipes)[2];
	pid_t	pid;
	int		read_fd;
	int		write_fd;
}	t_cmd;

typedef struct s_env
{
	char	***env;
	int		real_shlvl;
} t_env;

// checker.c
bool	check_builtin(t_cmd *command);

// parsing.c
t_cmd	*parsing_module(char **envp, char *read_line, t_cmd *commands);
char	**cmds_parse(char *read_line);
void	cmd_args_parse(t_cmd *commands, char **envp);

// freeing.c
void	free_module(t_cmd *cmds_struc, char *read_line, char *prmpt_path);
void	free_arr_of_arr(char **split);
void	free_structs(t_cmd *commands);

// fork_and_processes.c
void	exec_cmd(t_cmd cmd, int read_fd, int write_fd, char ***envp);
void	init_pipes(t_cmd *commands);
void	parent_process(t_cmd *commands);
void	child_process(t_cmd *commands, int i, char ***envp);
void	forking(t_cmd *commands, char ***envp);

//struct.c
void	init_cmds_struc(t_cmd *cmd_struc, int index);
t_cmd	*create_cmds_struc(char **cmds_splits, t_cmd *cmds_struc);
void	init_env_struc(t_env *global, char **envp);

// util_env.c
char	**copy_env_arr(char **envp);
int		get_env_count(char **envp);
int		add_env(char *arg, char ***envp);
char	**env_exists(char *arg, char **envp);

// util_export.c
void	bubble_sort(char **arr, int count);
int		print_sorted_env(char **envp);

// util_split.c:
char	**split_v2(char const *s, char c);

// util_path.c:
char	*find_cmd_path(char *command, char **envp);

// util_strjoin.c:
size_t	strlen_v2(const char *s);
char	*strnstr_v2(const char *haystack, const char *needle, size_t len);
char	*strjoin_v2(char const *s1, char const *s2);

// util_others.c
char	*itoa_v2(int n);
int		ft_isdigit_v3(int c);
int		atoi_v2(const char *str);

// util_others2.c
char	*strdup_v2(const char *s1);
char	*substr_v2(char const *s, unsigned int start, size_t len);

// built-ins
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd, char ***envp);

int		ft_env(t_cmd *cmd, char **envp);

void	ft_exit(t_cmd *cmd, char **envp);

// execution.c
void	execution_module(t_cmd *commands, char ***envp);
void	execute_builtin(t_cmd *cmd, char ***envp);

//minishell.c
 void	incr_or_decr_env_shlvl(char **envp, bool increase);

#endif
