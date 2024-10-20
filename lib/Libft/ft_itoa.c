/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 21:06:09 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/25 02:19:37 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	process_int(int *n, int len, int *neg)
{
	int	n_tmp;

	if (*n <= 0)
	{
		if (*n < 0)
			*neg += 1;
		if (*n == INT_MIN)
		{
			*neg += 1;
			*n += 1;
		}
		*n *= -1;
		len++;
	}
	n_tmp = *n;
	while (n_tmp)
	{
		n_tmp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		neg;

	neg = 0;
	len = process_int(&n, 0, &neg);
	str = (char *) malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (neg > 1)
	{
		str[--len] = '8';
		neg--;
		n /= 10;
	}
	while (len--)
	{
		str[len] = n % 10 + 48;
		n /= 10;
		if (neg)
			str[0] = '-';
	}
	return (str);
}
