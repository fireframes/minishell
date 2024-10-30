/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendswith.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:50:20 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/05/09 20:05:36 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strendswith(const char *s, const char *end)
{
	const char	*end0;

	if (!s || !end)
		return (0);
	end0 = &s[ft_strlen(s) - ft_strlen(end)];
	if (ft_strncmp(end0, end, ft_strlen(end)) == 0)
		return (1);
	return (0);
}
