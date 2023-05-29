/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:10:35 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/29 17:58:11 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(char **line, int *index)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) < 0)
		perror("error - pipe");
	g_data.jump_fork = 1;
	pid = fork();
	if (pid == -1)
		perror("error - fork");
	else if (pid > 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	}
	else
	{
		if (ft_strlen(line[*index]) == 1 && line[*index][0] == '|')
			*index += 1;
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, WUNTRACED);
		ft_check_next_comand(line, index);
		exit(1);
	}
}

void ft_check_next_comand(char **line, int *index)
{
/* 	if (line[*index] == NULL)
		ft_get_comand_pipe();
	else  */if (ft_its_a_redirector(line[*index], ft_strlen(line[*index])) >= 1)
		ft_redirector(line, index);
	else if (ft_its_a_builtins(line[*index]) == 1)
		ft_builtins(line, index);
	else if (ft_execute_ft_system(line, index) != -1)
		printf("seria um erro\n");
}

void	ft_get_comand_pipe(void)
{

}
