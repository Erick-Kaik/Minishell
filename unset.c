/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:12:25 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/17 10:41:11 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//vem o unset e dps tem q pegar todos os indices da frente e apagar, msm q algum no meio n apague o resto sim


//n ta funcionando n apaga 🤡
void ft_unset(char **line, int *index)
{
    *index += 1;
    while (line[*index] != NULL && ft_its_a_redirector(line[*index]) == 0)
    {
        if (ft_check_exist_var(line[*index]) == 1)
        {
            ft_printf("entrouuuu\n");
            ft_delete_var(line[*index]);
        }
        *index += 1;
    }
}

int ft_check_exist_var(char *name_var)
{
    t_var *aux;

    aux = g_data.var;
    while (aux != NULL)
    {
        if (ft_strncmp(aux->name, name_var, ft_strlen(aux->name)) == 0)
            return (1);
        aux = aux->next;
    }
    return (0);
}

void ft_delete_var(char *name_var)
{
    t_var *aux;
	t_var *temp;

	aux = g_data.var;
	temp = aux;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->next->name, name_var, ft_strlen(temp->next->name)) == 0)
		{
			if (temp->next == NULL)
                free(temp);
			else
				temp->next = temp->next->next;
			break ;
		}
		temp = temp->next;
	}
	g_data.var = aux;
}