/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:08:11 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/08 20:35:46 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (command == NULL)
// 	return (-1);

// ALL COMMAND INPUT ARGUMENTS GO IN AS 1 STRING
// cmd: echo $SHELL ss SD//SAD
// ret: /bin/zsh ss SD//SAD

// parse the command arg string to expand $
// the string for echo is the whole string
// how do we know it's just -n for args[1]

// check argument count?

// use printf or write? currently output is not recognized when piping

// EXPANDER should expand $ in any case!

int	write_str(char *str)
{
	int	i;

	i = 1;
	if (!str)
	{
		write(1, "(null)", 7);
		return (i);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}


int	write_nbr(long num, int base)
{
	char	*b;

	b = "0123456789abcdef";
	if (num < 0 && base == 10)
		return (write(1, "-", 1) + write_nbr(num * -1, base));
	if (num < 0 && base == 16)
		return write_nbr((unsigned int) num, base);
	if (num / base == 0)
		return write(1, &b[num % base], 1);
	return (write_nbr(num / base, base) + write_nbr(num % base, base));
}

int	expander(char *str, t_env *envp)
{
	int		offset;
	char 	*env_value;

	offset = 1;
	str++;
	if (!*str)
	{
		write(1, "$", 1);
		return (offset);
	}
	if (*str == '?')
	{
		offset = write_nbr((long) envp->exit_code, 10) + 1;
		return (offset);
	}
	if (!env_exists(str, *envp->env))
	{
		write(1, "\0", 1);
		offset = 0;
	}
	else
	{
		env_value = ft_strchr(*env_exists(str, *envp->env), '=');
		offset = write_str(env_value);
	}
	return (offset);
}

int	ft_echo(t_cmd *cmd, t_env *envp)
{
	int		i;
	int		newline;
	char	*str;
	int		expand_offset;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		str = cmd->args[i];
		while (*str)
		{
			expand_offset = 1;
			if (*str == '$')
			{
				expand_offset = expander(str, envp);
				if (expand_offset == 0)
				{
					str++;
					continue ;
				}
			}
			else
				write(1, str, 1);
			str += expand_offset;
		}
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
