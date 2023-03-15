/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:06:39 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/15 17:02:36 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(char **line, int *index)
{
    char path[PATH_MAX];
    int ret;

    *index += 1;
    g_data.pwd.pdw = *index;
    while (line[*index] != NULL)
    {
        ret = ft_its_a_redirector(line[*index]);
        if (ret == 1)
        {
            ft_redirector(line, index);
            g_data.pwd.fd = g_data.fd;
        }
        else if (ret == 2)
            break; //seria o pipe
        else
            break;
    }
    if (getcwd(path, sizeof(path)) != NULL)
        g_data.pwd.print = path;
    ft_putstr_fd(g_data.pwd.print, g_data.pwd.fd);
}