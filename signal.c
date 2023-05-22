/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:33:46 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 15:55:49 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_start_signals(void)
{
    struct sigaction sa_prompt;
    struct sigaction sa_close;

    sa_prompt.sa_handler = &ft_sig_new_prompt;
    sa_prompt.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_prompt.sa_mask);
    sigaction(SIGINT, &sa_prompt, NULL);

    sa_close.sa_handler = SIG_IGN;
    sa_close.sa_flags = 0;
    sigemptyset(&sa_close.sa_mask);
    sigaction(SIGQUIT, &sa_close, NULL);
}

void ft_sig_new_prompt(int sig)
{
    (void)sig;
    ft_putchar('\n');
    ft_clear_struct();
    kill(1, SIGKILL);
}

void ft_sig_close(int sig)
{   
    (void)sig;
    ft_putchar('\n');
    ft_clear_struct();
    kill(1, SIGKILL);
}

void ft_clear_pid(pid_t pid)
{
    g_data.pid = 0;
    kill(pid, SIGKILL);
}
