/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/29 01:06:11 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_in_child = 0;

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

static int	has_only_sp_or_tab_chars(char *read_line, char *prompt)
{
	int	i;

	if (!read_line)
		return (-1);
	i = 0;
	while (read_line[i] != '\0')
	{
		if (read_line[i] != ' ' && read_line[i] != '\t')
			return (0);
		i++;
	}
	free(prompt);
	free(read_line);
	return (1);
}

// IMPORTANT QUESTION: should the error message be output to fd 1 or 2?
// NOTE: no need to return (0) at the end of the main, is seems (?)
int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt;
	t_env	*env;

	setup_main_signals();
	read_line = NULL;
	prompt = NULL;
	check_args(argc, argv);
	env = init_env_struc_and_shlvl(envp);
	while (1)
	{
		prompt = get_curr_dir();
		read_line = readline(prompt);
		if (!read_line)
		{
			ft_exit(NULL, env, read_line, prompt);
			if (env->real_shlvl > 0)
			{
				free(prompt);
				continue ;
			}
		}
		if (has_only_sp_or_tab_chars(read_line, prompt) == 1)
			continue ;
		else if (has_only_sp_or_tab_chars(read_line, prompt) == -1)
		{
// TODO: LOOK INTO THIS ISSUE
			printf("something broke\n");
			break ;
		}
		if (*read_line)
			main_module(env, read_line, prompt);
	}
	if (read_line)
		free(read_line);
	free_on_exit(&env, prompt);
}
