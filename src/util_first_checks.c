/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/01 13:15:08 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_curr_dir(void)
{
	static char	curr_dir[PATH_MAX + 1];
	char		*full_prompt;

	full_prompt = strjoin_v2(getcwd(curr_dir, sizeof(curr_dir)), "$ ");
	return (full_prompt);
}

void	check_args(int argc, char **argv)
{
	(void) argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell: program should be run without arguments\n", 2);
		exit (1);
	}
}

int	has_only_sp_or_tab_chars(char *read_line, char *prompt)
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
