/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:33:44 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/15 17:38:03 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char **line, int *index)
{
    int ret;

    g_data.echo.echo = *index;
    if (ft_strlen(line[*index + 1]) == 2 && line[*index + 1][0] == '-'
        && line[*index + 1][1] == 'n')
    {
        g_data.echo.flag = 1;
        *index += 1;
    }
    *index += 1;
    while (line[*index] != NULL)
    {
        ret = ft_its_a_redirector(line[*index]);
        if (ret == 1)
        {
            ft_redirector(line, index);
            g_data.echo.fd = g_data.fd;
        }
        else if (ret == 2)
            break;
        else
        {
            if (g_data.echo.print == NULL)
                g_data.echo.print = ft_strjoin(g_data.echo.print, line[*index]);
            else
                g_data.echo.print = ft_strjoin_mod(g_data.echo.print, line[*index]);
            g_data.echo.print = ft_strjoin_mod(g_data.echo.print, " ");
            *index += 1;
        }
    }
    ft_putstr_fd(g_data.echo.print, g_data.echo.fd);
    if (g_data.echo.flag != 1)
        ft_putchar_fd('\n', g_data.echo.fd);
}