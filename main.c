/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:30:08 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/16 22:36:56 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int main (int argc, char **argv, char **envp)
{
    char *line;
    
    if (argc > 1 || argv == NULL)
        return (0);
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
    }
    return (0);
}
