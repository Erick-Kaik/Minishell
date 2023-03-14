/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:38:34 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/13 17:53:40 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(char **line, int *index)
{
    t_var *aux;

	aux = g_data.var;
    if (line[*index + 1] != NULL && ft_its_a_redirector(line[*index + 1]) == 0)
    {
        ft_printf("%s: '%s': No such file or directory\n", line[*index] ,line[*index + 1]);
        aux = NULL;
    }
	while (aux != NULL)
	{
		if (ft_strncmp(aux->name, "$?", ft_strlen(aux->name)) == 0)
		{
			aux = aux->next;
			continue ;
		}
        //precisava concatenar toda a string (todas as var, no g_data.print), porem so esta salvando o ultimo
        g_data.print = ft_strjoin(aux->name, "=");
        g_data.print = ft_strjoin_mod(g_data.print, aux->content);
        g_data.print = ft_strjoin_mod(g_data.print, "\n");

/* 		ft_putstr_fd(aux->name, g_data.fd);
		ft_putchar_fd('=', g_data.fd);
		ft_putstr_fd(aux->content, g_data.fd);
		ft_putchar_fd('\n', g_data.fd); */
		aux = aux->next;
	}
    while (line[*index] != NULL && ft_its_a_redirector(line[*index]) == 0)
        *index += 1;  
}