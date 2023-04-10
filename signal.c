/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:48:59 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/09 09:29:53 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_signals(void)
{
    struct sigaction sa_prompt;
    struct sigaction sa_close;

    sa_prompt.sa_handler = &ft_sig_new_prompt;
    sa_prompt.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_prompt.sa_mask);
    sigaction(SIGINT, &sa_prompt, NULL);

    sa_close.sa_handler = &ft_sig_close;
    sa_close.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_close.sa_mask);
    sigaction(SIGQUIT, &sa_close, NULL);
}

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

    (void)sig;
    var = ft_create_and_send_var(0, NULL);
    ft_add_value_last_com(&var, "130");
    ft_putchar_fd('\n', 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    kill(0, SIGKILL);
}


void ft_sig_close(int sig)
{
	t_var *var;
	t_history *history;

    var = ft_create_and_send_var(0, NULL);
    history = ft_create_and_send_history(0);
    ft_putchar_fd('\n', 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    if (sig == 3)
        ft_add_value_last_com(&var, "131");
    else
    {
        ft_clear_var(&var, ft_del_var);
        ft_clear_history(&history, ft_del_history);
        exit(1);
    }
} 
