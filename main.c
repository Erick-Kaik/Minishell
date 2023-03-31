/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:30:08 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/30 14:17:23 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int main (int argc, char **argv, char **envp)
{
    char *line;
    
    (void)argc;
    (void)argv;
    ft_starting_variables(envp);
    ft_start_signals();
    while (1)
    {
        ft_get_folder();
        line = readline(" ");
        if (line == NULL)
            ft_sig_close(0);
        ft_check_line(line);
        ft_clear_struct();
        free(line);
        //criar ft para printar coisas tipo echo e limpar as structs
    }
    return (0);
}

