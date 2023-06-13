/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:33:44 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/16 19:26:23 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **line, int *index)
{
	char	*aux;

	g_data.echo.echo = 1;
	aux = NULL;
	g_data.echo.print = NULL;
	if (ft_strlen(line[*index + 1]) == 2 && line[*index + 1][0] == '-'
			&& line[*index + 1][1] == 'n')
	{
		g_data.echo.flag = 1;
		*index += 1;
	}
	*index += 1;
	ft_get_str_echo(line, index);
	if (g_data.echo.print != NULL)
		aux = ft_strtrim(g_data.echo.print, " ");
	if (g_data.echo.print != NULL && g_data.echo.flag != 1)
		printf("%s\n", aux);
	else if (g_data.echo.print != NULL && g_data.echo.flag == 1)
		ft_putstr(aux);
	free(aux);
	g_data.exit_status = ft_strdup("0");
}

void	ft_get_str_echo(char **line, int *i)
{
	while (line[*i] != NULL)
	{
		if (ft_its_a_redirector(line[*i], ft_strlen(line[*i])) == 1
			&& line[*i + 1] != NULL && ft_strlen(line[*i + 1]) > 0)
		{
			ft_redirector(line, i);
			if (ft_strlen(line[*i]) == 1 && line[*i][0] == '|')
			{
				while (line[*i] != NULL)
					*i += 1;
			}
		}
		else
		{
			if (g_data.echo.print == NULL)
				g_data.echo.print = ft_strjoin(g_data.echo.print, line[*i]);
			else
				g_data.echo.print = ft_strjoin_mod(g_data.echo.print,
						line[*i]);
			g_data.echo.print = ft_strjoin_mod(g_data.echo.print, " ");
			*i += 1;
		}
	}
}

void	ft_clear_echo(void)
{
	if (g_data.echo.echo > 0)
		g_data.echo.echo = 0;
	if (g_data.echo.fd != 0)
		g_data.echo.fd = 0;
	if (g_data.echo.flag > 0)
		g_data.echo.flag = 0;
	if (g_data.echo.print != NULL)
	{
		free(g_data.echo.print);
		g_data.echo.print = NULL;
	}
}
