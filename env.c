/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:38:34 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/15 17:12:37 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(char **line, int *index)
{
    g_data.env.env = *index;
    if (line[*index + 1] != NULL && ft_its_a_redirector(line[*index + 1]) == 0)
        ft_printf("%s: '%s': No such file or directory\n", line[*index] ,line[*index + 1]);
    else
        ft_get_print_env();
    while (line[*index] != NULL && ft_its_a_redirector(line[*index]) == 0)
        *index += 1;  
}

void ft_get_print_env(void)
{
    t_var *aux;

	aux = g_data.var;
	while (aux != NULL)
	{
		if (ft_strncmp(aux->name, "$?", ft_strlen(aux->name)) == 0)
		{
			aux = aux->next;
			continue ;
		}
        if (g_data.env.print == NULL)
            g_data.env.print = ft_strjoin(g_data.env.print ,aux->name);
        else
            g_data.env.print = ft_strjoin_mod(g_data.env.print ,aux->name);
        g_data.env.print = ft_strjoin_mod(g_data.env.print, "=");
        g_data.env.print = ft_strjoin_mod(g_data.env.print, aux->content);
        g_data.env.print = ft_strjoin_mod(g_data.env.print, "\n");
		aux = aux->next;
	}
    
}