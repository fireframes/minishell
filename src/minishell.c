/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/21 19:21:13 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: should freeing mallocated memory have its own module instead
//	of being inside execution module?
void	main_module(t_env *envp, char *read_line, char *prompt_with_path)
{
	t_cmd	*cmds_struc;

	cmds_struc = NULL;
	add_history(read_line);
	cmds_struc = parsing_module(envp, read_line, cmds_struc);
	execution_module(cmds_struc, envp);
	free_module(cmds_struc, read_line, prompt_with_path);
}

// NOTE: based on current implementation of ft_pwd, taking the same assumptions
// -> should be modified if ft_pwd (esp. regarding buffer size)
static char	*get_curr_dir(void)
{
	static char	curr_dir[PATH_MAX + 1];
	char		*full_prompt;

	full_prompt = strjoin_v2(getcwd(curr_dir, sizeof(curr_dir)), "$ ");
	return (full_prompt);
}

static void	check_nb_of_args(int argc)
{
	if (argc != 1)
	{
		printf("minishell: program should be run without arguments\n");
		exit (1);
	}
}

static int	has_only_sp_or_tab_chars(char *read_line, char *prompt_w_path)
{
	int	i;

	i = 0;
	while (read_line[i] != '\0')
	{
		if (read_line[i] != ' ' && read_line[i] != '\t')
			return (0);
		i++;
	}
	free(prompt_w_path);
	free(read_line);
	return (1);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
// QUESTION: - should we free envp in the end of main?
//			 - need to print error on envp error?
// 			 - where to free when exiting with signals?
// IMPORTANT QUESTION: should the error message be output to fd 1 or 2?
// volatile sig_atomic_t	interrupt = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt_w_path;
	t_env	*env;

	(void) argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	check_nb_of_args(argc);
	env = init_env_struc(envp);
	incr_or_decr_env_shlvl(env, true);
	while (1)
	{
		prompt_w_path = get_curr_dir();
		read_line = readline(prompt_w_path);
		if (!read_line)
		{
			printf("exit\n");
			break ;
		}
		if (has_only_sp_or_tab_chars(read_line, prompt_w_path) == 1)
			continue ;
		if (*read_line)
			main_module(env, read_line, prompt_w_path);
	}
	free_on_exit(&env, prompt_w_path);
	return (0);
}
