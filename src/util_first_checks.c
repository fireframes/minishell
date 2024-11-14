/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_first_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:34:56 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/14 15:36:19 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_curr_dir(void)
{
	char	*pwd;
	char	*curr_dir;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	curr_dir = strjoin_v2(pwd, "$ ");
	free(pwd);
	return (curr_dir);
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

int	has_only_sp_or_tab_chars(char *read_line)
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
	free(read_line);
	return (1);
}
