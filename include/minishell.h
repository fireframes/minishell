/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/17 16:57:26 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_SHLVL 999

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

typedef struct s_env
{
	char	***env;
	int		real_shlvl;
	int		exit_code;
	bool	redir_syntax_err;
}	t_env;

typedef struct s_expand
{
	char	*expanded;
	int		*inquotes;
}	t_expnd;

typedef struct s_cmd
{
	char	**cmds_splits;
	int		total_cmds;
	char	**args;
	int		total_args;
	char	*cmd_path;
	int		command_index;
	bool	is_builtin;
	bool	path_found;
	bool	minishell_call;
	int		(*pipes)[2];
	pid_t	pid;
	int		read_fd;
	int		write_fd;
	char	*redir_part;
	char	**redirs;
	bool	redir_syntax_err;
	int		redir_amount;
}	t_cmd;

// checker.c
bool	check_builtin(t_cmd *command);

// parsing.c
t_cmd	*parsing_module(t_env *envp, char *read_line, t_cmd *commands);

// dequoter.c
// expander.c
// char	*expander(char *str, t_env *envp, t_cmd *t_qoute);
t_expnd	*dequote_expand(char *read_line, t_env *envp);

// redirections.c
void	redir_parsing_module(t_cmd *cmds_struc, t_env *envp);

// redirections_2.c
void	alloc_redir_arr(t_cmd *cmds_struc, int i);
int		find_1st_redir_type(char *str);

// freeing.c
void	free_module(t_cmd *cmds_struc, char *read_line, char *prmpt_path);
void	free_arr_of_arr(char **split);
void	free_structs(t_cmd *commands);
void	free_expand(t_expnd *expand);
void	free_on_exit(t_env **envp, char *prompt);

// fork_and_processes.c
void	exec_cmd(t_cmd cmd, int read_fd, int write_fd, t_env *envp);
void	init_pipes(t_cmd *commands);
void	parent_process(t_cmd *commands, t_env *envp);
void	child_process(t_cmd *commands, int i, t_env *envp);
void	forking(t_cmd *commands, t_env *envp);

//struct.c
void	init_cmds_struc(t_cmd *cmd_struc, int index);
t_cmd	*create_cmds_struc(char **cmds_splits, t_cmd *cmds_struc);
t_env	*init_env_struc(char **envp);

// util_env.c
char	**copy_env(char **envp);
int		get_env_count(char **envp);
size_t	get_env_len(char *str);
char	**env_exists(char *arg, char **envp);
bool	isvalid_arg(char *arg);

// util_export.c
void	bubble_sort(char **arr, int count);
int		print_sorted_env(char **envp);

// util_split.c
char	**split_v2(char const *s, char c);

// util_shlvl.c
void	incr_or_decr_env_shlvl(t_env *envp, bool increase);

// util_path.c
char	*find_cmd_path(char *command, char **envp);

// util_strjoin.c
int		strncmp_v2(const char *s1, const char *s2, size_t n);
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
int		ft_pwd(void);
int		ft_export(t_cmd *cmd, t_env *envp);
int		add_env(char *arg, t_env *envp);
int		ft_unset(t_cmd *cmd, t_env *envp);
int		ft_env(t_cmd *cmd, char **envp);
void	ft_exit(t_cmd *cmd, t_env *envp);

// execution.c
void	execution_module(t_cmd *commands, t_env *envp);
void	execute_builtin(t_cmd *cmd, t_env *envp);

#endif
