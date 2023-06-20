/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:10:35 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/02 10:59:37 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_create_fork_pipe(int *fd, pid_t *pid);

void	ft_pipe(char **line, int *index)
{
	int		fd[2];
	pid_t	pid;

	if (line[*index + 1] == NULL)
		return ;
	if (ft_create_fork_pipe(fd, &pid) == -1)
		return ;
	else if (pid == 0)
	{
		close(fd[0]);
		ioctl(fd[1], FIONBIO, &g_data.non_blocking);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	else
	{
		if (ft_strlen(line[*index]) == 1 && line[*index][0] == '|')
			*index += 1;
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		waitpid(pid, NULL, WUNTRACED);
		ft_check_next_comand(line, index, 1);
		exit(1);
	}
}

void	ft_check_next_comand(char **line, int *index, int in_pipe)
{
	if (ft_its_a_redirector(line[*index], ft_strlen(line[*index])) >= 1)
		ft_redirector(line, index);
	else if (ft_its_a_builtins(line[*index]) == 1)
		ft_builtins(line, index);
	else if (ft_execute_ft_system(line, index) == -1)
		ft_print_error(line, index);
	if (in_pipe == 1)
		ft_clear_struct();
}

void	ft_redirector_in_exec(char **line, int *index)
{
	while (line[*index] != NULL)
	{
		if (ft_its_a_redirector(line[*index], ft_strlen(line[*index])) > 0)
		{
			ft_redirector(line, index);
			if (ft_strlen(line[*index]) == 1 && line[*index][0] == '|'
				&& g_data.jump_fork == 1)
				break ;
			if (g_data.fd == -1)
			{
				*index -= 1;
				ft_print_error(line, index);
			}
		}
		else
			break ;
	}
}

static int	ft_create_fork_pipe(int *fd, pid_t *pid)
{
	if (pipe(fd) < 0)
	{
		ft_printf("Minishell - pipe creation error\n");
		return (-1);
	}
	g_data.jump_fork = 1;
	*pid = fork();
	if (*pid == -1)
	{
		g_data.jump_fork = 0;
		ft_printf("Minishell - fork creation error\n");
		return (-1);
	}
	return (0);
}
