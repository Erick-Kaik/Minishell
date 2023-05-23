/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:33:44 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/16 19:26:23 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char **line, int *index)
{
    g_data.echo.echo = 1;
    if (ft_strlen(line[*index + 1]) == 2 && line[*index + 1][0] == '-'
        && line[*index + 1][1] == 'n')
    {
        g_data.echo.flag = 1;
        *index += 1;
    }
    *index += 1;
    ft_get_str_echo(line, index);
    ft_putstr_fd(g_data.echo.print, g_data.echo.fd);
    if (g_data.echo.flag != 1)
        ft_putchar_fd('\n', g_data.echo.fd);
}

void ft_get_str_echo(char **line, int *index)
{
    int ret;

    while (line[*index] != NULL)
    {
        ret = ft_its_a_redirector(line[*index], ft_strlen(line[*index]));
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
}

void ft_clear_echo(void)
{
    if (g_data.echo.echo > 0)
        g_data.echo.echo = 0;
    if (g_data.echo.fd != 0)
        g_data.echo.fd = 0;
    if (g_data.echo.flag > 0)
        g_data.echo.flag = 0;
    if (g_data.echo.print != NULL)
    {
        free(g_data.echo.print);
        g_data.echo.print = NULL;
    }
}
