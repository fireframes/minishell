/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/14 15:37:43 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_module(t_env *envp, char *read_line)
{
	t_cmd	*cmds_struc;

	cmds_struc = NULL;
	setup_child_signals();
	add_history(read_line);
	cmds_struc = parsing_module(envp, read_line, cmds_struc);
	if (cmds_struc)
		execution_module(cmds_struc, envp);
	free_module(cmds_struc, read_line);
}

void	main_loop(char *read_line, char *prompt, t_env *env)
{
	while (1)
	{
		setup_main_signals();
		prompt = get_curr_dir();
		read_line = readline(prompt);
		free(prompt);
		if (!read_line)
		{
			ft_exit(NULL, env, read_line);
			if (env->real_shlvl > 0)
				continue ;
		}
		if (has_only_sp_or_tab_chars(read_line) == 1)
			continue ;
		else if (has_only_sp_or_tab_chars(read_line) == -1)
			break ;
		if (*read_line)
			main_module(env, read_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt;
	t_env	*env;

	read_line = NULL;
	prompt = NULL;
	check_args(argc, argv);
	env = init_env_struc_and_shlvl(envp);
	main_loop(read_line, prompt, env);
	if (read_line)
		free(read_line);
	free_on_exit(&env);
}
