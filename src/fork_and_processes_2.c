/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_processes_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/19 15:21:15 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// NOTE: this function and the next one (out_append()) could be blend into one.
void	out_create(t_cmd *cm, int i, int j)
{
	cm[i].last_fd_out = open(cm[i].redirs[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cm[i].last_fd_out <= 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cm[i].redirs[j], 2);
        ft_putstr_fd(": ", 2);
		perror(NULL);
		exit(1);
	}
}

void	out_append(t_cmd *cm, int i, int j)
{
	cm[i].last_fd_out = open(cm[i].redirs[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cm[i].last_fd_out <= 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cm[i].redirs[j], 2);
        ft_putstr_fd(": ", 2);
		perror(NULL);
		exit(1);
	}
}

void	in_read(t_cmd *cm, int i, int j)
{
	cm[i].last_fd_in = open(cm[i].redirs[j], O_RDONLY);
	if (cm[i].last_fd_in <= 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cm[i].redirs[j], 2);
        ft_putstr_fd(": ", 2);
		perror(NULL);
		exit(1);
	}
}

void	handle_files(t_cmd *cm, int i)
{
	int	j;

	j = 0;
    if (cm[i].redirs != NULL)
    {
        while (cm[i].redirs[j] != NULL)
        {
            if (cm[i].redirs[j][0] == '>' && cm[i].redirs[j][1] == '>')
                out_create(cm, i, (j + 1));
            else if (cm[i].redirs[j][0] == '>')
                out_append(cm, i, (j + 1));
            else if (cm[i].redirs[j][0] == '<' && cm[i].redirs[j][1] == '\0')
                in_read(cm, i, (j + 1));
            j = j + 2;
        }
    }
}
