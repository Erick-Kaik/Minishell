/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:54:56 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/09 14:57:06 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_value_exit_execve(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			g_data.exit_status = ft_strdup("130");
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf("Quit");
			g_data.exit_status = ft_strdup("131");
		}
		ft_printf("\n");
		exit(1);
	}
	else if (WIFEXITED(status))
		g_data.exit_status = ft_itoa(WEXITSTATUS(status));
}
void ft_update_status_code(char **spt, int *i)
{
	t_var	*aux;
	t_var	*temp;

	aux = g_data.var;
	temp = aux;
	*i += 1;
	while (temp != NULL)
	{
		if (temp->name[0] == '?' && ft_strlen(temp->name) == 1)
		{
			if (temp->content != NULL)
				free(temp->content);
			temp->content = ft_strdup(spt[*i]);
			break ;
		}
		temp = temp->next;
	}
	g_data.var = aux;
}
