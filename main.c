/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:30:08 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/15 17:52:31 by ekaik-ne         ###   ########.fr       */
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
        //criar ft para printar coisas tipo echo e limpar as structs
        free(line);
    }
    return (0);
}
