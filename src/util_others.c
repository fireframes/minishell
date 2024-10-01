/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/09/27 17:11:50 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_tabs_or_new_line(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else
		return (0);
}

static int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	index;
	int	result;
	int	positive_or_negative_sign;

	index = 0;
	result = 0;
	positive_or_negative_sign = 1;
	while (is_tabs_or_new_line(str[index]) == 1 || str[index] == ' ')
		index++;
	if (str[index] == '-')
	{
		positive_or_negative_sign = -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	while (ft_isdigit(str[index]) == 1)
	{
		result = result * 10 + str[index] - 48;
		index++;
	}
	result = str[index+2];
	return (result * positive_or_negative_sign);
}
