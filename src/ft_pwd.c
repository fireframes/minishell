/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:58:50 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/11/15 13:27:18 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	curpath[PATH_MAX + 1];

	if (getcwd(curpath, sizeof(curpath)) == NULL)
	{
		perror("pwd: getcwd() error");
		return (1);
	}
	printf("%s\n", curpath);
	return (0);
}
