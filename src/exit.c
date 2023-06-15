/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:25:11 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/10 18:01:31 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_send_to_parent(void);

void	ft_exit(char **line)
{
	int	pipe;
	int	x;

	x = 0;
	pipe = 0;
	while (line[x])
	{
		if (ft_its_a_redirector(line[x], ft_strlen(line[x])) == 1)
		{
			ft_redirector(line, &x);
			if (ft_strlen(line[x]) == 1 && line[x][0] == '|')
			{
				x++;
				pipe = 1;
			}
		}
		x++;
	}
	if (pipe == 0)
		ft_send_to_parent();
	ft_clear_struct();
	ft_close_default_fd();
	exit(1);
}

static void	ft_send_to_parent(void)
{
	if (g_data.pid == 0)
	{
		close(g_data.pipe[0]);
		ft_putstr_fd("exit;", g_data.pipe[1]);
		ft_putstr_fd("1", g_data.pipe[1]);
	}
}

void	ft_exit_parent(char **split, char *line)
{
	ft_clear_struct();
	ft_clear_split_line(split);
	if (split != NULL)
		free(split);
	free(line);
	printf("logout\n");
	ft_close_default_fd();
	exit(1);
}
