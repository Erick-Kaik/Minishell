/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:00:34 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 19:44:18 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*ft_new_lst_history(char *num, char *comand)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->num = num;
	new->comand = comand;
	return (new);
}

void	ft_add_lst_history(t_history **history, t_history *new)
{
	t_history	*aux;

	if (history == NULL || new == NULL)
		return ;
	if (*history == NULL)
	{
		*history = new;
		return ;
	}
	aux = ft_lst_history_last(*history);
	aux->next = new;
}

t_history *ft_lst_history_last(t_history *history)
{
	if (history == NULL)
		return (NULL);
	while (history->next != NULL)
		history = history->next;
	return (history);
}

int ft_get_size_history(t_history *history)
{
	int size;
	t_history *lst;

	size = 0;
	lst = history;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	ft_clear_history(t_history **history, void (*del)(char*))
{
	t_history	*aux;

	if (history == NULL || del == NULL)
		return ;
	while (*history != NULL)
	{
		aux = (*history)->next;
		ft_del_one_history(*history, del);
		*history = aux;
	}
	*history = NULL;
}

void	ft_del_one_history(t_history *history, void (*del)(char*))
{	
	if (history == NULL || del == NULL)
		return ;
	del(history->num);
	del(history->comand);
	free(history);
}

void	ft_del_history(char *content)
{
	content = NULL;
	if (content != NULL)
		free(content);
	else
		return ;
}
