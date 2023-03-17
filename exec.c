/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:47:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/17 16:32:22 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//crair uma ft para limitar a quatidade do argv (tipo ate os limitadores)

#include "minishell.h"

int ft_execute_ft_system(char **line, int *index)
{
    char **aux;
    char *path;
    int ret;

    ret = 0;
    //da um fork, ai usa o filho pra executar enquanto o pai espera
    //dps da free no aux (de dentro pra fora)
    aux = ft_limit_execve(line, index);
    if (aux == NULL)
        return (0);
    path = ft_strjoin("/bin/", aux[0]);
    ret = execve(path, aux, g_data.envp);
    return (ret);
}

char **ft_limit_execve(char **line, int *index)
{
    int x;
    int y;
    char **aux;

    x = 0;
    y = 0;
    while (line[*index + x] != NULL && ft_its_a_redirector(line[*index + x]) == 0)
        x++;
    aux = (char **)malloc(sizeof(char *) * (x + 1));
    if (aux == NULL)
        return (NULL);
    while (y < x)
    {
        aux[y] = ft_strdup(line[*index + y]);
        y++;
    }
    aux[y] = NULL;
    *index += x;
    return (aux);
}