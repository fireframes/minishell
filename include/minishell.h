/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:20:05 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_SHLVL 999

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include "linux/limits.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
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
	char	*prompt;
	char	*read_line;
	int		real_shlvl;
	int		exit_code;
	bool	redir_syntax_err;
	bool	final_exit;
	int		total_heredocs_in_all;
}	t_env;

typedef struct s_expand
{
	char	*expanded;
	int		*inquotes;
}	t_expnd;

typedef struct s_quote
{
	bool	sngl_quote;
	bool	dbl_quote;
	bool	isquoted;
}	t_quote;

typedef struct s_expand_data
{
	char	*line;
	t_env	*envp;
	t_quote	*quote;
	char	*expanded;
	int		*inquotes;
	int		i;
	int		j;
}	t_expd_data;

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
	int		last_fd_in;
	int		last_fd_out;
	int		heredocs_amount;
	t_env	*env;
}	t_cmd;

typedef struct s_split_data
{
	const char	*str;
	char		delimiter;
	int			*inquotes;
	size_t		i;
	size_t		words;
	char		**split_array;
}	t_split_data;

// checker.c
bool	check_builtin(t_cmd *command);

// parsing.c
t_cmd	*parsing_module(t_env *envp, char *read_line, t_cmd *commands);

// parsing_2.c
char	**cmds_parse(char *read_line, int *inquotes);

// dequoter.c
t_expnd	*dequote_expand(char *read_line, t_env *envp);
bool	dequoter(char *line, t_quote *quote);
int		*init_inquotes(int inquotes[]);

// expander.c
t_expnd	*expander(char *line, t_env *envp, t_quote *quote);
int		is_expandable_env(char *line_ptr, t_env *envp, char *expanded, int *j);

// redirections.c
void	redir_parsing_module(t_cmd *cmds_struc, t_env *envp, int *inquotes);

// redirections_2.c
void	isolate_redir_part(t_cmd *cmds_struc, int *inquotes);

// redirections_3.c
void	alloc_redir_arr(t_cmd *cmds_struc, int i);
int		handle_builtin_redirections(t_cmd *cmd);

// freeing.c
void	free_module(t_cmd *cmds_struc, char *read_line);
void	free_arr_of_arr(char **split);
void	free_structs(t_cmd *commands);
void	free_expand(t_expnd *expand);
void	free_on_exit(t_env **envp);

// fork_and_processes.c
void	exec_cmd(t_cmd cmd, int read_fd, int write_fd, t_env *envp);
void	parent_process(t_cmd *commands, t_env *envp);
void	child_process(t_cmd *commands, int i, t_env *envp);
void	forking(t_cmd *commands, t_env *envp);

// fork_and_processes_2.c
void	init_pipes(t_cmd *commands);
void	handle_files_redir(t_cmd *c_struc, int i);

//struct.c
void	init_cmds_struc(t_cmd *cmd_struc, int index);
t_cmd	*create_cmds_struc(char **cmds_splits, t_cmd *cmds_struc, t_env *envp);
t_env	*init_env_struc_and_shlvl(char **envp);

//util_expand.c
void	process_line(t_expd_data *data);
void	handle_dollar_sign(t_expd_data *data);
void	handle_env_var(t_expd_data *data);
void	handle_exit_code(t_expd_data *data);
void	init_expand(t_expd_data *data, char *line, t_env *envp, t_quote *quote);

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
char	**split_v1(char const *s, char c);
char	**split_v2(char const *s, char c, int *inquotes);
size_t	count_word_length(t_split_data *d);

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
int		mini_strcat(char *dest, const char *src);

// built-ins
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(void);
int		ft_export(t_cmd *cmd, t_env *envp);
int		add_env(char *arg, t_env *envp);
int		ft_unset(t_cmd *cmd, t_env *envp);
int		ft_env(t_cmd *cmd, char **envp);
int		ft_exit(t_cmd *cmd, t_env *envp, char *read_line);

// execution.c
void	execution_module(t_cmd *commands, t_env *envp);
void	execute_builtin(t_cmd *cmd, t_env *envp);
int		apply_redirections(char **redirs);

// signals.c
void	setup_main_signals(void);
void	setup_child_signals(void);

// util_first_checks.c
char	*get_curr_dir(void);
void	check_args(int argc, char **argv);
int		has_only_sp_or_tab_chars(char *read_line);

#endif
