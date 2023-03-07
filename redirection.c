/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:09:47 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/06 14:49:19 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_get_file(char *str)
{
    int x;
    int y;
    int z;
    char *file;

    x = 1;
    y = 0;
    z = 0;
    while ((str[x] == 32 || str[x] == 9) && str[x] != '\0')
        x++;
    while ((str[x + y] != 32 || str[x + y] != 9) && str[x + y] != '\0' && str[x + y] != '\n')
        y++;
    file = malloc((y + 1) * sizeof(char));
    while (z < y)
    {
        file[z] = str[x + z];
        z++;
    }
    file[z] = '\0';
    return (file);
}

int ft_rd_output(char *str)
{
    int x;
    int fd;
    char *file;

    x = -1;
    while (str[++x] != '\0')
        if (str[x] == '>')
            break;
    file = ft_get_file(&str[x]);
    fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_SYNC, 0644);
    return (fd);
}

int ft_rd_last_output(char *str)
{
    int x;
    int fd;
    char *file;

    x = -1;
    while (str[++x] != '\0')
        if (str[x] == '>' && str[x + 1] == '>')
            break;
    x++;
	file = ft_get_file(&str[x]);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    return (fd);
}

int ft_rd_input(char *str)
{
    int x;
    int fd;
    char *file;

    x = -1;
    fd = 0;
    file = str;
    return (fd);
}

int ft_rd_loop_input(char *str)
{
    int x;
    int fd;
    char *file;

    x = -1;
    fd = 0;
    file = str;
    return (fd);
}
