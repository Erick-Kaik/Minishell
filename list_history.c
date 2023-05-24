/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:39:05 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/24 10:44:14 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*ft_new_lst_history(char *content)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->str = content;
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

t_history   *ft_lst_history_last(t_history *history)
{
	if (history == NULL)
		return (NULL);
	while (history->next != NULL)
		history = history->next;
	return (history);
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
	del(history->str);
	free(history);
}

void	ft_del_history(char *content)
{
	if (content != NULL)
		free(content);
	else
		return ;
}
