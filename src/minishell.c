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

volatile sig_atomic_t	g_in_child = 0;

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

void	main_loop(char *read_line, char *prompt, t_env *env)
{
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
			break ;
		if (*read_line)
			main_module(env, read_line, prompt);
	}
}

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
	main_loop(read_line, prompt, env);
	if (read_line)
		free(read_line);
	free_on_exit(&env, prompt);
}
