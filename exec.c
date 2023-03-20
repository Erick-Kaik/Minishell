/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:47:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/20 17:05:48 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//crair uma ft para limitar a quatidade do argv (tipo ate os limitadores)

#include "minishell.h"

int ft_execute_ft_system(char **line, int *index)
{
    char **aux;
    char *path;
    int ret;
    int status;
    pid_t pid;

    ret = 0;
    status = 0;
    //da um fork, ai usa o filho pra executar enquanto o pai espera
    //dps da free no aux (de dentro pra fora)
    
    aux = ft_limit_execve(line, index);
    if (aux == NULL)
        return (0);
    path = ft_strjoin("/bin/", aux[0]);
    pid = fork();
    if (pid == 0)
    {
        ret = execve(path, aux, g_data.envp);
/*         if (ret != -1)
            kill(pid, SIGKILL);
        else */
        exit(ret);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, WUNTRACED);
        if (status > 0)
            ret = -1;
    }
    free(path);
    ft_clear_split_line(aux);
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