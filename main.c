/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:50:15 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/09 09:34:15 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char**envp)
{
    pid_t pid;
	char		*comand;
	t_var		*var;
	t_history	*history;

    (void)argc;
    (void)argv;
    pid = fork();
	var = ft_create_and_send_var(1, envp);
	history = ft_create_and_send_history(1);
    ft_signals();
	while (1)
	{
        if (pid == 0)
            comand = readline(ft_get_folder());
		if (comand != NULL && pid == 0)
		{
			ft_read_comand(comand, &var, &history);
			free (comand);
		}
        else if (comand == NULL)
            ft_sig_close(0);
        wait(NULL);
        pid = fork();
	}
	return (0);
}
