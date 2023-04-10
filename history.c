/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:45:24 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/08 10:41:04 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_history(char *str, t_history *history, t_var **var)
{
	t_history *aux;
	int fd;

	aux = history;
	fd = ft_check_redirector(str);
	while (aux != NULL)
	{
		ft_putstr_fd(aux->num, fd);
		ft_putchar_fd(' ', fd);
		ft_putstr_fd(aux->comand, fd);
		if (aux->comand[ft_strlen(aux->comand) - 1] != '\n')
			ft_putchar_fd('\n', fd);
		aux = aux->next;
	}
	ft_add_value_last_com(var, "0");
}

void ft_add_history(char *str, t_history **history)
{
	int number;
	char *s_number;
	t_history *aux;

	if (ft_strnstr(str, "<<", ft_strlen(str)) != NULL)
		return ;
	aux = *history;
	number = ft_atoi(aux->num);
	if (ft_strlen(str) == 1 && str[0] == '\n')
		return ;
	if (number == 0)
	{
		aux->num = "1";
		str = ft_save_str_history(str);
		aux->comand = str;
		*history = aux;
	}
	else
	{
		number = ft_get_size_history(*history) + 1;
		s_number = ft_itoa(number);
		str = ft_save_str_history(str);
		ft_add_lst_history(history, ft_new_lst_history(s_number, str));
	}
}

char *ft_save_str_history(char *str)
{
	int size;
	int x;
	char *aux;

	x = 0;
	size = ft_strlen(str);
	aux = malloc(sizeof(char) * size);
	if (aux == NULL)
		return (NULL);
	while (x < size)
	{
		aux[x] = str[x];
		x++;
	}
	aux[x] = '\0';
	return (aux);
}
