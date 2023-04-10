/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:49:42 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/13 16:00:02 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(char *str, t_var **var)
{
	int fd;
	
	fd = ft_check_redirector(str);
	ft_print_env_other_var(fd, *var);
	ft_add_value_last_com(var, "0");
}

void ft_print_env_other_var(int fd, t_var *var)
{
	t_var *aux;


	aux = var;
	while (aux != NULL)
	{
		if (ft_strncmp(aux->name, "$?", ft_strlen(aux->name)) == 0)
		{
			aux = aux->next;
			continue ;
		}
		ft_putstr_fd(aux->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(aux->content, fd);
		ft_putchar_fd('\n', fd);
		aux = aux->next;
	}
}