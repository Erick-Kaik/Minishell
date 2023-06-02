/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:12:25 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/12 13:24:38 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_send_to_parent(char *value);

void	ft_unset(char **line, int *index)
{
	*index += 1;
	while (line[*index] != NULL && ft_its_a_redirector(line[*index],
			ft_strlen(line[*index])) == 0)
	{
		if (ft_check_exist_var(line[*index]) == 1)
		{
			ft_delete_var(line[*index]);
			if (g_data.pid == 0)
				ft_send_to_parent(line[*index]);
		}
		*index += 1;
	}
}

static void	ft_send_to_parent(char *value)
{
	if (g_data.pid == 0)
	{
		close(g_data.pipe[0]);
		ft_putstr_fd("unset:", g_data.pipe[1]);
		ft_putstr_fd(value, g_data.pipe[1]);
	}
}

int	ft_check_exist_var(char *name_var)
{
	t_var	*aux;

	aux = g_data.var;
	while (aux != NULL)
	{
		if (ft_strncmp(aux->name, name_var, ft_strlen(aux->name)) == 0)
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	ft_delete_var(char *name_var)
{
	t_var	*aux;
	t_var	*temp;

	aux = g_data.var;
	temp = aux;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->next->name, name_var,
				ft_strlen(temp->next->name)) == 0)
		{
			if (temp->next == NULL)
				free(temp);
			else
				temp->next = temp->next->next;
			ft_clear_env();
			break ;
		}
		temp = temp->next;
	}
	g_data.var = aux;
}
