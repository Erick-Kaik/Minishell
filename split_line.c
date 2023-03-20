/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:36:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/20 15:43:09 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_broke_line(char *line) //fazer um tratamento, caso haja aspas (duplas ou simples) tem q tratar tudo q esta dentro
{                               // como um indice do tempo, oq estiver fora pode ser no split msm
    // int i;
    // int index;
    char *aux;
    char **temp;

    // i = 0;
    aux = ft_strtrim(line, " ");
    // index = ft_count_split(line);
    // temp = (char **)malloc(sizeof(char *) * (index + 1));
    // while (i < index)
    // {

    // }
    temp = ft_split(aux, ' ');
    free(aux);
    return (temp);
}

char *ft_get_var(char *name_var)
{
    t_var *aux;

    aux = g_data.var;
    while (aux != NULL)
    {
        if (ft_strncmp(aux->name, name_var, ft_strlen(aux->name)) == 0)
            return (aux->content);
        aux = aux->next;
    }
    return (NULL);
}

int ft_count_split(char *str)
{    
    int i;
    int count;
    int quotes;
    
    i = 0;
    count = 0;
    quotes = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ' && quotes == 0)
            count++;
        else if ((str[i] == 34 || str[i] == 39) && quotes == 0)
        {
            count++;
            quotes = str[i];
        }
        else if (quotes > 0 && str[i] == quotes)
            quotes = 0;
        i++;
    }
    return (quotes);
}

/*
1° ft -> conta quantas linhas vao ter nas Char**
2° ft -> aplica o conteudo de str na linha splitada, assim fnzd o tratamento (cria o malloc fora da 1 e da 2)

//split somente entre espacos e tudo dentro das aspas é 1 coias so
 */