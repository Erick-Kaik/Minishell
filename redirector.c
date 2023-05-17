/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:58:33 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/16 20:15:09 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_redirector(char **line, int *index)
{
    if (ft_strlen(line[*index]) == 2)
    {
        if (line[*index][0] == '>' && line[*index][1] == '>')
            ft_appending(line, index);
        else if (line[*index][0] == '<' && line[*index][1] == '<')   
            ft_here_doc(line, index);
    }
    else if (ft_strlen(line[*index]) == 1)
    {
        if (line[*index][0] == '>')
            ft_overwriting(line, index);
        else if (line[*index][0] == '<')
            ft_input(line, index);
/*      else if (line[*index][0] == '|')
            ft_pipe(); */
    }
}

void    ft_appending(char **line, int *index)
{    
    char aux_path[PATH_MAX];

    getcwd(aux_path, sizeof(aux_path));
    if (aux_path != NULL)
        chdir(g_data.path_comand);
    if (ft_strlen(line[*index]) == 2
        && line[*index][0] == '>' && line[*index][1] == '>')
        *index += 1;
    else
        return;
        
    g_data.fd = open(line[*index], O_RDWR | O_CREAT | O_APPEND | O_SYNC, 0644);
    if (aux_path != NULL)
        chdir(aux_path);
    *index += 1;
}

void ft_overwriting(char **line, int *index)
{    
    char aux_path[PATH_MAX];

    getcwd(aux_path, sizeof(aux_path));
    if (aux_path != NULL)
        chdir(g_data.path_comand);
    if (ft_strlen(line[*index]) == 1 && line[*index][0] == '>')
        *index += 1;
    else
        return;
    g_data.fd = open(line[*index], O_RDWR | O_CREAT | O_TRUNC | O_SYNC, 0644);
    if (aux_path != NULL)
        chdir(aux_path);
    *index += 1;
}

void  ft_here_doc(char **line, int *index)
{
    char *aux;

    if (ft_strlen(line[*index]) == 2 && line[*index][0] == '<'
        && line[*index][1] == '<')
        *index += 1;
    while (1)
    {
        rl_on_new_line();
        aux = readline("> ");
        if (aux == NULL)
            ft_sig_close(0);
        if (ft_strlen(line[*index]) == ft_strlen(aux)
            && ft_strnstr(line[*index], aux, ft_strlen(line[*index])) != NULL)
            break;
        free(aux);
    }
    free(aux);
    *index += 1;
}

void ft_input(char **line, int *index) // preciso fazer ainda
{
    if (ft_strlen(line[*index]) == 1 && line[*index][0] == '<')
        *index += 1;
    else
        *index += 1;
    return;
}
