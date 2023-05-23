/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:47:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 17:15:38 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int ft_execute_ft_system(char **line, int *index)
{
    char **aux;
    char *path;
    int ret;
    int status;
    pid_t pid;

    ret = 0;
    status = 0;    
    aux = ft_limit_execve(line, index);
    if (aux == NULL)
        return (0);
    path = ft_strjoin("/bin/", aux[0]);
    pid = fork();
    if (pid == 0)
    {
        if (line[*index] != NULL && ft_its_a_redirector(line[*index], ft_strlen(line[*index])) > 0)
            ft_redirector(line, index);
        ret = execve(path, aux, g_data.envp);
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
    while (line[*index + x] != NULL && ft_its_a_redirector(line[*index + x],
        ft_strlen(line[*index + x])) == 0)
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
} */


int ft_execute_ft_system(char **line, int *index)
{
    char **aux;
    char *path;
    int ret;
    aux = ft_limit_execve(line, index);
    if (aux == NULL)
        return (0);
    path = ft_strjoin("/bin/", aux[0]);
    ret = ft_execute_execve(aux, line, path, index);
    free(path);
    ft_clear_split_line(aux);
    return (ret);
}

int ft_execute_execve(char **aux, char **line, char *path, int *index)
{
    int status;
    int ret;
    pid_t pid;

    ret = 0;
    status = 0;  
    pid = fork();
    if (pid == 0)
    {
        if (line[*index] != NULL && ft_its_a_redirector(line[*index],
            ft_strlen(line[*index])) > 0)
            ft_redirector(line, index);
        ret = execve(path, aux, g_data.envp);
        exit(ret);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, WUNTRACED);
        if (status > 0)
             ret = -1;
    }
    return (ret);
}


char **ft_limit_execve(char **line, int *index)
{
    int x;
    int y;
    char **aux;

    x = 0;
    y = 0;
    while (line[*index + x] != NULL && ft_its_a_redirector(line[*index + x],
        ft_strlen(line[*index + x])) == 0)
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