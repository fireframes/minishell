/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaksimo <mmaksimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:03:49 by mmaksimo          #+#    #+#             */
/*   Updated: 2024/10/09 12:04:20 by mmaksimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static bool is_a_redir(char *arg)
// {
//     if (strncmp_v2(arg, ">", 1) == 0 || strncmp_v2(arg, ">>", 2) == 0
//         || strncmp_v2(arg, "<", 1) == 0)
//     {
//         return (true);
//     }
//     else
//         return (false);
// }

// void    count_redirections(t_cmd *cmds_struc)
// {
//     int i;
//     int j;

//     i = 0;
//     count_args(cmds_struc);
//     while (i < cmds_struc->total_cmds)
//     {
//         j = 0;
//         while (j < cmds_struc[i].total_args)
//         {
//             if (is_a_redir(cmds_struc[i].args[j]) == true)
//                 cmds_struc[i].redir_amount++;
//             j++;
//         }
//         i++;
//     }
// }
