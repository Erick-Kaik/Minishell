/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:33:46 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/30 15:11:13 by ekaik-ne         ###   ########.fr       */
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
	if (g_data.pid > 0)
        ft_clear_pid(g_data.pid);
    ft_putchar_fd('\n', 1);
    rl_replace_line("", 0);
    if (g_data.pid == 0)
        ft_get_folder();
    rl_on_new_line();
    rl_redisplay();
}

void ft_sig_close(int sig)
{   
    (void)sig;
    ft_clear_struct();
    exit(0);
}

void ft_clear_pid(pid_t pid)
{
    g_data.pid = 0;
    kill(pid, SIGKILL);
}