/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:32:11 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 19:44:06 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*ft_new_lst_var(char *title, char *value)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->name = title;
	new->content = value;
	return (new);
}

void	ft_add_lst_var(t_var **var, t_var *new)
{
	t_var	*aux;

	if (var == NULL || new == NULL)
		return ;
	if (*var == NULL)
	{
		*var = new;
		return ;
	}
	aux = ft_lst_var_last(*var);
	aux->next = new;
}

t_var *ft_lst_var_last(t_var *var)
{
	if (var == NULL)
		return (NULL);
	while (var->next != NULL)
		var = var->next;
	return (var);
}

void	ft_clear_var(t_var **var, void (*del)(char*))
{
	t_var	*aux;

	if (var == NULL || del == NULL)
		return ;
	while (*var != NULL)
	{
		aux = (*var)->next;
		ft_del_one_var(*var, del);
		*var = aux;
	}
	*var = NULL;
}

void	ft_del_one_var(t_var *var, void (*del)(char*))
{	
	if (var == NULL || del == NULL)
		return ;
	del(var->name);
	del(var->content);
	free(var);
}

void	ft_del_var(char *content)
{
	content = NULL;
	if (content != NULL)
		free(content);
	else
		return ;
}
