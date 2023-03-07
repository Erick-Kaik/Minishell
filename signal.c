/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:48:59 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 21:21:03 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var *ft_create_and_send_var(int create, char **env)
{
	static t_var *var;
	char **temp;
	int index;
	
	if (create == 1 && env != NULL)
	{
		index = 0;
		while (env[index] != NULL)
		{
			temp = ft_split(env[index], '=');
			if (var == NULL)
				var = ft_new_lst_var(temp[0], temp[1]);
			else
				ft_add_lst_var(&var, ft_new_lst_var(temp[0], temp[1]));
			index++;
		}
		ft_add_lst_var(&var, ft_new_lst_var("$?", "0"));
	}
	return (var);
}

t_history *ft_create_and_send_history(int create)
{
	static t_history *history;

	if (create == 1 || history == NULL)
		history = ft_new_lst_history("0", "");
	return (history);
}

void ft_sig_new_prompt(int sig)
{
	t_var *var;

	if (sig == SIGINT)
	{
		var = ft_create_and_send_var(0, NULL);
		ft_add_value_last_com(&var, "130");
		ft_printf("\n");
		ft_get_folder();
		pause();
	}
	//querba de linha a imprimir o novo prompt (coder:~/MiniHell $->)
}


void ft_sig_close(int sig)
{
	t_var *var;
	t_history *history;

	if (sig == SIGQUIT)
	{
		//usar esse esquema no exit tmb
		var = ft_create_and_send_var(0, NULL);
		history = ft_create_and_send_history(0);
		
		ft_clear_var(&var, ft_del_var);
		ft_clear_history(&history, ft_del_history);
		exit(1);
	}
	//quando entrar aqui vou ter q mandar algo para poder dar clear na list
} 


