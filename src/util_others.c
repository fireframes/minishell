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

static int	length(long n)
{
	long	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_v2(int n)
{
	char	*str;
	int		i;
	long	n_l;

	str = (char *)malloc(sizeof(char) * (length((long) n) + 1));
	if (str == NULL)
		return (NULL);
	n_l = (long) n;
	i = length((long) n) - 1;
	str[i + 1] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n_l = n_l * -1;
	}
	if (n == 0)
		str[i] = '0';
	while (n_l != 0)
	{
		str[i--] = (n_l % 10) + 48;
		n_l = n_l / 10;
	}
	return (str);
}

static int	is_tabs_or_new_line(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	else
		return (0);
}

int	ft_isdigit_v3(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

// QUESTION: what was the use of the line commented out in this function?
int	ft_atoi_v2(const char *str)
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
	while (ft_isdigit_v3(str[index]) == 1)
	{
		result = result * 10 + str[index] - 48;
		index++;
	}
	// result = str[index+2];
	return (result * positive_or_negative_sign);
}
