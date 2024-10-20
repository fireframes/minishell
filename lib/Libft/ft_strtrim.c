/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:14:41 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/02/23 21:35:28 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	trim_len;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (start < ft_strlen(s1) && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		end--;
	trim_len = end - start + 2;
	trim = (char *) malloc(trim_len * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, &s1[start], trim_len);
	return (trim);
}

/*
rtf
rrftr-arfgrrr
0123456789012
check any other char not from set is in the leading part of s1
and return its pointer *start
get the difference between it and 0 pointer diff_lead

check any other char not from set is in the trailing part of s1
and return its pointer *end
get the difference between it and the end of string  diff_trail

trim_len = (ft_strlen(s1) - (d_lead + d_trail);
trim = (char *) malloc(new_str_len + 1)) * sizeof(char));
ft_strlcpy(trim, start, new_str_len);

*/
