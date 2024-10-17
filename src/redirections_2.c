/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/16 12:04:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_redir_sign(t_cmd *c, int i, int j, int k)
{
    int l;

    l = 0;
    if (c[i].redir_part[k] == '>' && c[i].redir_part[k + 1] == '>')
    {
        c[i].redirs[j][l] = '>';
        l++;
        c[i].redirs[j][l] = '>';
        l++;
        k = k + 2;
    }
    else
    {
        c[i].redirs[j][l] = c[i].redir_part[k];
        l++;
        k++;
    }
    c[i].redirs[j][l] = '\0';
    return (k);
}

static int	copy_filename(t_cmd *c, int i, int j, int k)
{
    int l;

    l = 0;
    while (c[i].redir_part[k] == ' ')
        k++;
    while (c[i].redir_part[k] != '<' && c[i].redir_part[k] != '>' &&
        c[i].redir_part[k] != '\0' && c[i].redir_part[k] != ' ')
    {
        c[i].redirs[j][l] = c[i].redir_part[k];
        l++;
        k++;
    }
    c[i].redirs[j][l] = '\0';
    while (c[i].redir_part[k] != '<' && c[i].redir_part[k] != '>' &&
        c[i].redir_part[k] != '\0')
            k++;
    return (k);
}

void	alloc_redir_arr(t_cmd *c, int i)
{
    int	j;
    int k;

    j = 0;
    k = 0;
	c[i].redirs = malloc(sizeof(char **) * (c[i].redir_amount * 2 + 1));
	while (j < (c[i].redir_amount * 2))
	{
		c[i].redirs[j] = malloc(sizeof(char *) * (ft_strlen(c[i].redir_part)
			+ 1));
        if (j%2 == 0)
			k = copy_redir_sign(c, i, j, k);
        else
			k = copy_filename(c, i, j, k);
		j++;
	}
    c[i].redirs[j] = NULL;
}

int	find_1st_redir_type(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
			return (1);
		if (str[i] == '>')
			return (2);
		i++;
	}
	return (0);
}
