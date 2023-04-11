/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:26:18 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/10 19:06:19 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_its_a_redirector(char *line)
{
    if (line == NULL || ft_strlen(line) > 2)
        return (0);
    if (ft_strlen(line) == 2)
    {
        if ((line[0] == '>' && line[1] == '>')
            || (line[0] == '<' && line[1] == '<')) 
            return (1);
    }
    else if (ft_strlen(line) == 1)
    {
        if (line[0] == '>' || line[0] == '<')
            return (1);
        else if (line[0] == '|')
            return (2);
    }
    return (0);
}

int ft_its_a_builtins(char *line)
{
    ft_printf("line = %s\n", line);
    if (line == NULL || ft_strlen(line) > 6)
        return (0);
    if (ft_strlen(line) == 2 && ft_strnstr(line, "cd", 2) != NULL)
        return (1);
    else if (ft_strlen(line) == 3 && (ft_strnstr(line, "env", 3) != NULL
        || ft_strnstr(line, "pwd", 3) != NULL))
        return (1);
    else if (ft_strlen(line) == 4 && (ft_strnstr(line, "echo", 4) != NULL
        || ft_strnstr(line, "exit", 4) != NULL))
        return (1);
    else if (ft_strlen(line) == 5 && ft_strnstr(line, "unset", 5) != NULL)
        return (1);
    else if (ft_strlen(line) == 6 && ft_strnstr(line, "export", 6) != NULL)
        return (1);
    else
        return (0);
}

void    ft_print_error(char **line, int *index)
{
    char *aux;

    g_data.error.error += 1;
    if (line[*index] == NULL)
        *index -= 1;
    aux = ft_strjoin("bash: ", line[*index]);
    aux = ft_strjoin_mod(aux, ": command not found\n");
    ft_putstr_fd(aux, 0);
    free(aux);
    while (line[*index] != NULL && ft_its_a_redirector(line[*index]) == 0)
        *index += 1;
}
