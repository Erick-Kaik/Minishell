/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:17:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/10 18:01:01 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(char **line, int *index)
{
    int value;
    char *path;

    value = 0;
    path = ft_get_path_cd(line, index);
    if (path != NULL)
    {
        if (ft_strlen(path) == 1 && path[0] == '~')
            value = chdir(getenv("HOME"));
        else
            value = chdir(path);
    }
    if (value == -1)
        ft_printf("bash: %s: '%s': No such file or directory\n",
            line[*index], line[*index + 1]);
    if (path != NULL)
        free(path);
    while (line[*index] != NULL && ft_its_a_redirector(line[*index]) == 0)
        *index += 1;    
}

char *ft_get_path_cd(char **line, int *index)
{
    char *path;

    path = NULL;
    if (line[*index + 1] == NULL || ft_its_a_redirector(line[*index + 1]) == 1)
    {
        path = malloc(sizeof(char) * 1);
        path[0] = '~';
        path[1] = '\0';
    }
    else if (line[*index + 1] != NULL && ft_its_a_redirector(line[*index + 1]) == 0)
    {
        if (line[*index + 2] != NULL && ft_its_a_redirector(line[*index + 2]) == 0)
        {
            path = NULL;
            ft_printf("bash: %s: too many arguments\n", line[*index]);
        }
        else
            path = ft_strjoin(path, line[*index + 1]);
    }
    return (path);    
}
