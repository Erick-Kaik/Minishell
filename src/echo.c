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
	*index += 1;
	ft_check_flag(line, index);
	ft_get_str_echo(line, index);
	if (g_data.echo.print != NULL)
		aux = ft_strdup(g_data.echo.print);
	if (g_data.echo.print != NULL)
		ft_printf("%s", aux);
	if (g_data.echo.flag != 1)
		ft_printf("\n");
	free(aux);
	g_data.exit_status = ft_strdup("0");
}

void	ft_check_flag(char **str, int *index)
{
	size_t	i;

	if (str == NULL || str[*index] == NULL || ft_strlen(str[*index]) <= 1)
		return ;
	while (str[*index] != NULL)
	{
		i = 0;
		if (ft_strlen(str[*index]) > 1 && str[*index][i] != '-')
			return ;
		i++;
		while (str[*index][i] != '\0')
		{
			if (str[*index][i] != 'n')
				return ;
			i++;
		}
		g_data.echo.flag = 1;
		*index += 1;
	}
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
			if (line[*i + 1] != NULL && ft_its_a_redirector(line[*i + 1],
					ft_strlen(line[*i + 1])) == 0)
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
