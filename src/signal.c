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
	struct sigaction	sa_parent_int;
	struct sigaction	sa_parent_quit;

	sa_parent_int.sa_handler = &ft_new_prompt;
	sa_parent_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_parent_int.sa_mask);
	sigaction(SIGINT, &sa_parent_int, NULL);
	sa_parent_quit.sa_handler = SIG_IGN;
	sa_parent_quit.sa_flags = 0;
	sigemptyset(&sa_parent_quit.sa_mask);
	sigaction(SIGQUIT, &sa_parent_quit, NULL);
}

void	ft_new_prompt(int sig)
{
	char	**aux;
	int		i;

	i = 0;
	(void)sig;
	ft_putstr_fd("\n", 1);
	if (g_data.pid > 0)
		return ;
	aux = ft_split("?:130", ':');
	ft_update_status_code(aux, &i);
	ft_clear_split_line(aux);
	if (aux != NULL)
		free(aux);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_start_signal_child(void)
{
	struct sigaction	sa_child_int;
	struct sigaction	sa_child_quit;

	sa_child_int.sa_flags = 0;
	sa_child_int.sa_handler = &ft_kill_child;
	sigemptyset(&sa_child_int.sa_mask);
	sigaction(SIGINT, &sa_child_int, NULL);
	sa_child_quit.sa_handler = SIG_IGN;
	sa_child_quit.sa_flags = 0;
	sigemptyset(&sa_child_quit.sa_mask);
	sigaction(SIGQUIT, &sa_child_quit, NULL);
}

void	ft_kill_child(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	if (g_data.exit_status != NULL)
		free(g_data.exit_status);
	g_data.exit_status = ft_strdup("130");
	if (close(g_data.pipe[0]) == -1)
		ft_putstr_fd(":", g_data.pipe[1]);
	ft_putstr_fd("?:", g_data.pipe[1]);
	ft_putstr_fd(g_data.exit_status, g_data.pipe[1]);
	ft_clear_struct();
	ft_close_default_fd();
	exit(1);
}

void	ft_start_signal_execve(pid_t pid)
{
	struct sigaction	sa_execve;

	sa_execve.sa_flags = 0;
	sigemptyset(&sa_execve.sa_mask);
	if (pid == 0)
		sa_execve.sa_handler = SIG_DFL;
	else
		sa_execve.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_execve, NULL);
	sigaction(SIGQUIT, &sa_execve, NULL);
}
