/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/24 13:41:44 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_module(t_env *envp, char *read_line, char *prompt_with_path)
{
	t_cmd	*cmds_struc;

	cmds_struc = NULL;
	add_history(read_line);
	cmds_struc = parsing_module(envp, read_line, cmds_struc);
	if (cmds_struc)
		execution_module(cmds_struc, envp);
	free_module(cmds_struc, read_line, prompt_with_path);
}

static char	*get_curr_dir(void)
{
	static char	curr_dir[PATH_MAX + 1];
	char		*full_prompt;

	full_prompt = strjoin_v2(getcwd(curr_dir, sizeof(curr_dir)), "$ ");
	return (full_prompt);
}

static void	check_args(int argc, char **argv)
{
	(void) argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell: program should be run without arguments\n", 2);
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

// IMPORTANT QUESTION: should the error message be output to fd 1 or 2?
// volatile sig_atomic_t	interrupt = 0;
// NOTE: no need to return (0) at the end of the main, is seems (?)
int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt_w_path;
	t_env	*env;

	signal_module();
	read_line = NULL;
	prompt_w_path = NULL;
	check_args(argc, argv);
	env = init_env_struc_and_shlvl(envp);
	while (1)
	{
		prompt_w_path = get_curr_dir();
		read_line = readline(prompt_w_path);
		if (!read_line)
		{
			ft_exit(NULL, env);
			if (env->real_shlvl != 0)
				continue ;
		}
		if (has_only_sp_or_tab_chars(read_line, prompt_w_path) == 1)
			continue ;
		if (*read_line)
			main_module(env, read_line, prompt_w_path);
	}
	free_on_exit(&env, prompt_w_path);
}
