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

// static void	copy_redir_sign(t_cmd *c, int i, int j)
// {

// }

// static void	copy_filename(t_cmd *c, int i, int j)
// {

// }

// void	alloc_redir_arr(t_cmd *c, int i)
// {
//     int	j;

//     j = 0;
// 	c[i].redirs = malloc(sizeof(char **) * (c[i].redir_amount * 2 + 1));
// 	while (j < (c[i].redir_amount * 2))
// 	{
// 		c[i].redirs[j] = malloc(sizeof(char *) * (ft_strlen(c[i].redir_part)
// 			+ 1));
//         if (j%2 == 0)
// 			copy_redir_sign(c, i, j);
//         else
// 			copy_filename(c, i, j);
// 		j++;
// 	}
// }
