/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:58:33 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 17:11:20 by ekaik-ne         ###   ########.fr       */
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

void ft_input(char **line, int *index)  // troca o fd do terminal pro texto do bglh dps do '<'  pega todos, fznd em ordem se der erro ele trava e gera um erro
{                                       //se der erro break basicamente, e se funciona e dps tiver comandods preciso testar
    char aux_path[PATH_MAX];

    getcwd(aux_path, sizeof(aux_path));
    if (aux_path != NULL)
        chdir(g_data.path_comand);
    if (ft_strlen(line[*index]) == 1 && line[*index][0] == '<')
        *index += 1;
    ft_printf("before line = %s\n", line[*index]);
    while (line[*index] != NULL)
    {
        g_data.fd = open(line[*index], O_RDONLY | O_SYNC);
        if (g_data.fd < 0)
            ft_print_error(line, index);
        if (line[*index + 1] == NULL || ft_its_a_redirector(line[*index], ft_strlen(line[*index])) > 0)
            break;
    }     
    ft_printf("after line = %s\n", line[*index]);
    dup2(g_data.fd, STDIN_FILENO);
    close(STDIN_FILENO);
    if (aux_path != NULL)
        chdir(aux_path);
}
