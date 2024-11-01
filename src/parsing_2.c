/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/01 16:17:21 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmds_parse(char *read_line, int *inquotes)
{
	char	**cmds_splits;

	cmds_splits = NULL;
	cmds_splits = split_v3(read_line, '|', inquotes);
	if (!cmds_splits)
		return (NULL);
	return (cmds_splits);
}
