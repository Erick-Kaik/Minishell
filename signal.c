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

void	ft_start_signals_parent(void)
{
	struct sigaction	saParent_int;
	struct sigaction	saParent_quit;

	saParent_int.sa_handler = &ft_new_prompt;
	saParent_int.sa_flags = SA_RESTART;
	sigemptyset(&saParent_int.sa_mask);
	sigaction(SIGINT, &saParent_int, NULL);

	saParent_quit.sa_handler = SIG_IGN;
	saParent_quit.sa_flags = 0;
	sigemptyset(&saParent_quit.sa_mask);
	sigaction(SIGQUIT, &saParent_quit, NULL);
}

void	ft_new_prompt(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_get_folder();
	rl_redisplay();
}

void	ft_start_signal_child(void)
{
	struct sigaction	saChild_int;
	struct sigaction	saChild_quit;

	saChild_int.sa_flags = 0;
	saChild_int.sa_handler = &ft_kill_child;
	sigemptyset(&saChild_int.sa_mask);
	sigaction(SIGINT, &saChild_int, NULL);

	saChild_quit.sa_handler = SIG_IGN;
	saChild_quit.sa_flags = 0;
	sigemptyset(&saChild_quit.sa_mask);
	sigaction(SIGQUIT, &saChild_quit, NULL);
}

void	ft_kill_child(int sig)
{
	(void)sig;
	ft_clear_struct();
	exit(1);
}

void	ft_start_signal_execve(pid_t pid) /* Not working */
{
	struct sigaction	saExecve;

	saExecve.sa_flags = 0;
	sigemptyset(&saExecve.sa_mask);
	if (pid == 0)
		saExecve.sa_handler = &ft_kill_execve; /* Se for processo filho passa uma ft q faz quebra de linha, limpa e finaliza */
	else
		saExecve.sa_handler = SIG_IGN;
	sigaction(SIGINT, &saExecve, NULL);
	sigaction(SIGQUIT, &saExecve, NULL);
}

void	ft_kill_execve(int sig) /* duplicando terminal */
{
	(void)sig;
	ft_clear_struct();
	kill(1, SIGINT);
}
