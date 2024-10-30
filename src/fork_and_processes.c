/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/29 01:06:11 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	duplicate_and_close(int file_descriptor, int in_or_out)
{
	int	new_fd_for_check_only;

	new_fd_for_check_only = 0;
	if (in_or_out == STDIN_FILENO)
		new_fd_for_check_only = dup2(file_descriptor, STDIN_FILENO);
	else if (in_or_out == STDOUT_FILENO)
		new_fd_for_check_only = dup2(file_descriptor, STDOUT_FILENO);
	if (new_fd_for_check_only < 0)
		perror(NULL);
	close(file_descriptor);
}

void	exec_cmd(t_cmd cmds_struc, int read_fd, int write_fd, t_env *envp)
{
	if (cmds_struc.last_fd_in > 0)
		duplicate_and_close(cmds_struc.last_fd_in, STDIN_FILENO);
	else if (read_fd != STDIN_FILENO)
		duplicate_and_close(read_fd, STDIN_FILENO);
	if (cmds_struc.last_fd_out > 0)
		duplicate_and_close(cmds_struc.last_fd_out, STDOUT_FILENO);
	else if (write_fd != STDOUT_FILENO)
		duplicate_and_close(write_fd, STDOUT_FILENO);
	if (cmds_struc.is_builtin)
	{
		execute_builtin(&cmds_struc, envp);
		exit(EXIT_SUCCESS);
	}
	else if (cmds_struc.args == NULL)
	{
		free_struct(cmds_struc);
		exit(0);
	}
	else if (cmds_struc.path_found == false && access(cmds_struc.args[0], F_OK) == 0)
	{
		free_struct(cmds_struc);
		exit(126);
	}
	else if (cmds_struc.path_found == false && cmds_struc.is_builtin == false)
	{
		free_struct(cmds_struc);
		exit(127);
	}
	else
	{
		execve(cmds_struc.cmd_path, cmds_struc.args, envp->env[0]);
		perror("execve");
	}
}

void	parent_process(t_cmd *cmds_struc, t_env *envp)
{
	int	i;
	int	child_status_info;

	i = 0;
	child_status_info = 0;
	while (i < cmds_struc->total_cmds - 1)
	{
		close(cmds_struc->pipes[i][0]);
		close(cmds_struc->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < cmds_struc->total_cmds)
	{
		waitpid(cmds_struc[i].pid, &child_status_info, WUNTRACED);
		i++;
		if (i == cmds_struc->total_cmds)
			envp->exit_code = WEXITSTATUS(child_status_info);
	}
	if (WIFSIGNALED(child_status_info)
		&& WTERMSIG(child_status_info) == SIGQUIT)
		write(STDOUT_FILENO, "Quit\n", 6);
	g_in_child = 0;
	unlink(" ");
}

void	child_process(t_cmd *c_struc, int i, t_env *envp)
{
	int		j;

	handle_files_redir(c_struc, i);
	if (i == 0)
		c_struc[i].read_fd = STDIN_FILENO;
	else
		c_struc[i].read_fd = c_struc->pipes[i - 1][0];
	if (i == c_struc->total_cmds - 1)
		c_struc[i].write_fd = STDOUT_FILENO;
	else
		c_struc[i].write_fd = c_struc->pipes[i][1];
	j = 0;
	while (j < c_struc->total_cmds - 1)
	{
		if (j != i - 1)
			close(c_struc->pipes[j][0]);
		if (j != i)
			close(c_struc->pipes[j][1]);
		j++;
	}
	exec_cmd(c_struc[i], c_struc[i].read_fd, c_struc[i].write_fd, envp);
}

void	forking(t_cmd *cmds_struc, t_env *envp)
{
	int	i;

	i = 0;
	g_in_child = 1;
	while (i < cmds_struc->total_cmds)
	{
		if (cmds_struc[i].minishell_call != true)
		{
			cmds_struc[i].pid = fork();
			if (cmds_struc[i].pid == -1)
			{
				perror("fork");
				free_structs(cmds_struc);
			}
			else if (cmds_struc[i].pid == 0)
			{
				setup_child_signals();
				child_process(cmds_struc, i, envp);
			}
		}
		i++;
	}
	parent_process(cmds_struc, envp);
}
