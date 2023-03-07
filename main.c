/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:50:15 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 15:59:20 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char**envp)
{
	char		*comand;
	t_var		*var;
	t_history	*history;

	argc = 1;
	argv = NULL;
	var = ft_create_and_send_var(1, envp);
	history = ft_create_and_send_history(1);
	signal(SIGINT, ft_sig_new_prompt);
	signal(SIGQUIT, ft_sig_close);
	while (1)
	{
		ft_get_folder();
		comand = get_next_line(0);
		if (comand != NULL)
		{
			ft_read_comand(comand, &var, &history);
			free (comand);
		}
		else if (comand == NULL)
			ft_sig_close(SIGQUIT);
	}
	return (0);
}
