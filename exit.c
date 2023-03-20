/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:25:11 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/20 11:49:20 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(char **line)
{
    int x;

    x = 0;
    while (line[x] != NULL)
        free(line[x++]);
    if (line != NULL)
        free(line);
    ft_clear_struct();
    ft_putstr_fd("loggout\n", 0);
    exit (1);
}
