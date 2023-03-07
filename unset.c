/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:25:09 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 17:39:36 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(char *varaible, t_var **var)
{
	t_var *aux;
	t_var *temp;
	char *str;

	aux = *var;
	temp = aux;
	str = ft_jump_spaces(ft_strtrim(varaible, "\n"), "unset");
	if (str == NULL)
		return ;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->next->name, str, ft_strlen(temp->next->name)) == 0)
		{
			if (temp->next == NULL)
				free(temp);
			else
				temp->next = temp->next->next;
			break ;
		}
		temp = temp->next;
	}
	*var = aux;
}
