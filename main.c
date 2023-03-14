/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:30:08 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/13 16:29:14 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int main (int argc, char **argv, char **envp)
{
    char    *line;

    (void)argc;
    (void)argv;
    ft_starting_variables(envp);
    while (1)
    {
        ft_get_folder();
        line = readline(" ");
        //if (line == NULL)
            //Função de fechar
        ft_check_line(line);
        if (g_data.print != NULL)
        {
            ft_putstr_fd(g_data.print, g_data.fd);
            free(g_data.print);
        }
        free(line);
    }
    

    return (0);
}
