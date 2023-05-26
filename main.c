/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:30:08 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 15:58:38 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	char	*line;

	if (argc > 1 || argv == NULL)
		return (0);
	ft_starting_variables(envp);
	ft_start_signals();
	while (1)
	{
		pid = fork();
		if (pid > 0)
			g_data.pid = pid;
		if (pid < 0)
			continue;
		else if (pid == 0)
		{
			ft_get_folder();
			line = readline(" ");
			if (line == NULL)
				ft_sig_close(0);
			ft_check_line(line);
			ft_clear_struct();
			free(line);
			exit(1);
		}
		else if (pid > 0)
			waitpid(pid, NULL, WUNTRACED);
	}
	return (0);
}
