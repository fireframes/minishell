/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:44:57 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/01 20:15:56 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_main_handler(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_child_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n", 1);
}

static void	sigquit_child_handler(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "Quit\n", 6);
}

void	setup_main_signals(void)
{
	signal(SIGINT, sigint_main_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigquit_child_handler);
}
