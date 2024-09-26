/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:41:10 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/08/28 15:14:10 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_inside_array(char **arr_of_arr)
{
	int	i;

	i = 0;
	while (arr_of_arr[i] != NULL)
	{
		free(arr_of_arr[i]);
		i++;
	}
}

static char	*find_path_or_err(char **all_paths, char *cmd)
{
	char	*path_with_slash;
	char	*tried_command_path;
	int		i;

	i = 0;
	while (all_paths[i] != NULL)
	{
		path_with_slash = strjoin_v2(all_paths[i], "/");
		tried_command_path = strjoin_v2(path_with_slash, cmd);
		free(path_with_slash);
		if (access(tried_command_path, F_OK | X_OK) != -1)
		{
			free_inside_array(all_paths);
			free(all_paths);
			return (tried_command_path);
		}
		free(tried_command_path);
		i++;
	}
	free_inside_array(all_paths);
	free(all_paths);
	return (NULL);
}

// NOTE - starting at 2 because for some reason envp[1] is NULL and it messes
//	with the strnstr_v2 loop. TO BE MODIFIED anyway!
static char	*get_correct_cmd_path(char *cmd, char **envp)
{
	char	**all_existing_paths;
	char	*working_path_if_one;
	int		i;

	i = 2;
	while (envp[i] != NULL)
	{
		if (strnstr_v2(envp[i], "PATH=", 5) && envp[i])
			break ;
		i++;
	}
	all_existing_paths = split_v2(envp[i], ':');
	working_path_if_one = find_path_or_err(all_existing_paths, cmd);
	return (working_path_if_one);
}

char	*find_command_path(char *command, char **envp)
{
	char	*cmd_path;

	cmd_path = get_correct_cmd_path(command, envp);
	return (cmd_path);
}
