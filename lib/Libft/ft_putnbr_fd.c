/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:20:13 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/23 12:44:40 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_pow(int num)
{
	int		pow;

	pow = 0;
	while (num)
	{
		num /= 10;
		pow++;
	}
	pow--;
	return (pow);
}

static int	rec_pow(int base, int power)
{
	if (power == 0)
		return (1);
	else
		return (rec_pow(base, power - 1) * base);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		pow;

	if (n == 0 || n == INT_MIN)
	{
		if (n == 0)
			write(fd, "0", 1);
		else
			write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	pow = count_pow(n);
	while (pow + 1)
	{
		c = n / rec_pow(10, pow) + 48;
		write(fd, &c, 1);
		n %= rec_pow(10, pow);
		pow--;
	}
}
