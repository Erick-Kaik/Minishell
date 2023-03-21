/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:33:46 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/21 15:01:42 by ekaik-ne         ###   ########.fr       */
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

    sa_close.sa_handler = &ft_sig_close;
    sa_close.sa_flags = SA_SIGINFO;
    sigemptyset(&sa_close.sa_mask);
    sigaction(SIGQUIT, &sa_close, NULL);
}

void ft_sig_new_prompt(int sig)
{
    (void)sig;
	ft_putchar_fd('\n', 0);
    ft_get_folder();
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void ft_sig_close(int sig)
{
    (void)sig;
    ft_clear_struct();
    exit(0);
}