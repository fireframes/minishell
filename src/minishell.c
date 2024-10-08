/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/05 15:22:18 by mmaksimo         ###   ########.fr       */
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
		printf("minishell: program should be started without arguments\n");
		exit (1);
	}
}

// TODO: handle the case in which SHLVL has been unset (in that case, opening
//	another level of shell should resume to SHLVL=1)
// TODO?: handle the case in which SHLVL has been manually changed (via export)
//	to a value bigger to 999 or higher. In that case, output:
//		bash: warning: shell level (1000) too high, resetting to 1
// TODO?: if a negative number has been set to SHLVL via export, the next level
//	in the env should be 0
void	incr_or_decr_env_shlvl(char **envp, bool increase)
{
	int		i;
	char	*substr_1;
	char	*substr_2;
	int		shell_level_integer;

	i = 0;
	while (envp[i] != NULL)
	{
		if (strnstr_v2(envp[i], "SHLVL=", 6) && envp[i])
			break ;
		i++;
	}
	substr_1 = substr_v2(envp[i], 0, 6);
	substr_2 = substr_v2(envp[i], 6, strlen_v2(envp[i]) - 6);
	shell_level_integer = atoi_v2(substr_2);
	if (increase == true)
		shell_level_integer++;
	else
		shell_level_integer--;
	free(substr_2);
	substr_2 = itoa_v2(shell_level_integer);
	free(envp[i]);
	envp[i] = strjoin_v2(substr_1, substr_2);
	free(substr_1);
	free(substr_2);
}

// TODO: exit the infinite loop with SIGNALS;
// EOF (Ctrl+D) is dealt with the if (!read_line) {break} ; is that enough?
// QUESTION: - should we free envp in the end of main?
//			 - need to print error on envp error?
// 			 - where to free when exiting with signals?
int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt_w_path;
	t_env	*env;

	(void) argv;
	check_nb_of_args(argc);
	env = malloc(sizeof(t_env) * 1);
	init_env_struc(env, envp);
	incr_or_decr_env_shlvl(env->env[env->real_shlvl], true);
	while (1)
	{
		prompt_w_path = get_curr_dir();
		read_line = readline(prompt_w_path);
		if (!read_line)
			break ;
		if (*read_line)
			main_module(env, read_line, prompt_w_path);
	}
	free_arr_of_arr(env->env[env->real_shlvl]);
	free(env->env);
	return (0);
}
