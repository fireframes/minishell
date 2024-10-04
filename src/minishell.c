/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:16:31 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/02 19:22:44 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// QUESTION: should freeing mallocated memory have its own module instead
//	of being inside execution module?
void	main_module(char ***envp, char *read_line, char *prompt_with_path)
{
	t_cmd		*cmds_struc;

	cmds_struc = NULL;
	add_history(read_line);
	cmds_struc = parsing_module(*envp, read_line, cmds_struc);
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

// void	add_or_del_env_lvl()
// {

// }

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
// TODO: the main function is already 24 lines, should some part of it (such
//		as the nb of args check or the envp error check) moved to other
//		functions?
// QUESTION: - should we free envp in the end of main?
//			 - need to print error on envp error?
// 			 - where to free when exiting with signals?
int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	char	*prompt_with_path;
	char	***env;

	(void) argv;
	check_nb_of_args(argc);
	env = malloc(sizeof(char **) * MAX_SHLVL);
	if (env == NULL)
		return (2);
	env[0] = copy_env_arr(envp);
	if (env[0] == NULL)
		return (2);
	incr_or_decr_env_shlvl(env[0], true);
	while (1)
	{
		prompt_with_path = get_curr_dir();
		read_line = readline(prompt_with_path);
		if (!read_line)
			break ;
		if (*read_line)
			main_module(&env[0], read_line, prompt_with_path);
	}
	free_arr_of_arr(env[0]);
	free(env);
	return (0);
}
