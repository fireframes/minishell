/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_processes_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:26:33 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_cmd *cmds_struc)
{
	int	(*pipes)[2];
	int	i;

	pipes = NULL;
	pipes = malloc(sizeof(*pipes) * (cmds_struc->total_cmds - 1));
	if (!pipes)
		free_structs(cmds_struc);
	cmds_struc->pipes = pipes;
	i = 0;
	while (i < cmds_struc->total_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free_structs(cmds_struc);
		}
		i++;
	}
}

static void	out_write(t_cmd *cm, int i, int j, bool is_append)
{
	if (is_append == false)
		cm[i].last_fd_out = open(cm[i].redirs[j], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (is_append == true)
		cm[i].last_fd_out = open(cm[i].redirs[j], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (cm[i].last_fd_out <= 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cm[i].redirs[j], 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		exit(1);
	}
}

static void	in_read(t_cmd *cm, int i, int j)
{
	cm[i].last_fd_in = open(cm[i].redirs[j], O_RDONLY, 0644);
	if (cm[i].last_fd_in <= 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cm[i].redirs[j], 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		exit(1);
	}
}

static void	heredoc(t_cmd *cm, int i, int j)
{
	char		*read_heredoc;

	cm[i].last_fd_in = open(" ", O_WRONLY | O_CREAT, 0644);
	while (1)
	{
		read_heredoc = readline("> ");
		if (ft_strcmp(read_heredoc, cm[i].redirs[j]) == 0)
			break ;
		ft_putstr_fd(read_heredoc, cm[i].last_fd_in);
		ft_putstr_fd("\n", cm[i].last_fd_in);
		free(read_heredoc);
	}
	close(cm[i].last_fd_in);
	cm[i].last_fd_in = open(" ", O_RDONLY, 0644);
}

void	handle_files_redir(t_cmd *cm, int i)
{
	int	j;
	int	heredocs_in_cmd;

	heredocs_in_cmd = 0;
	j = 0;
	if (cm[i].redirs != NULL)
	{
		while (cm[i].redirs[j] != NULL)
		{
			if (cm[i].redirs[j][0] == '<' && cm[i].redirs[j][1] == '<')
			{
				heredocs_in_cmd++;
				if (heredocs_in_cmd == cm[i].heredocs_amount)
					heredoc(cm, i, (j + 1));
			}
			else if (cm[i].redirs[j][0] == '>' && cm[i].redirs[j][1] == '>')
				out_write(cm, i, (j + 1), true);
			else if (cm[i].redirs[j][0] == '>')
				out_write(cm, i, (j + 1), false);
			else if (cm[i].redirs[j][0] == '<' && cm[i].redirs[j][1] == '\0')
				in_read(cm, i, (j + 1));
			j = j + 2;
		}
	}
}
