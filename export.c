/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:55:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/16 14:06:16 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* criar uma ft para verificar se a o '='
pos split
1° indice é igual ao nome
2° indice pode ser o igual ou o valor tem q ver

 */


void ft_export(char **line, int *index)
{
    int x;
    char **aux;
    char *name;
    char *value;

    x = 0;
    if (line[*index + 1] != NULL && ft_strchr(line[*index + 1], '=') != NULL)
        *index += 1;
    else if (line[*index + 1] == NULL || ft_strchr(line[*index + 1], '=') == NULL)
    {
        *index += 1;
        return ;
    }
    aux = ft_split(line[*index], '=');
    while (aux[x] != NULL)
    {
        if (x == 0)
            name = ft_strdup(aux[x]);
        else if (x == 1)
            value = ft_strjoin(value, aux[x]);
        else
        {
            value = ft_strjoin_mod(value, "=");
            value = ft_strjoin_mod(value, aux[x]);
        }
        x++;
    }
    ft_add_lst_var(&g_data.var, ft_new_lst_var(name, value));
    while (line[*index] != NULL && ft_its_a_builtins(line[*index]) == 0)
        *index += 1;    
}