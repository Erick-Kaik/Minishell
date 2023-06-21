/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:26:18 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 13:03:33 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_send_to_parent(char *value, char *aux);

int	ft_its_a_redirector(char *line, int len)
{
	if (line == NULL || ft_strlen(line) <= 0 || ft_strlen(line) > 2)
		return (0);
	if (len == 2)
	{
		if ((line[0] == '>' && line[1] == '>')
			|| (line[0] == '<' && line[1] == '<'))
			return (1);
	}
	else if (len == 1)
	{
		if (line[0] == '>' || line[0] == '<' || line[0] == '|')
			return (1);
	}
	return (0);
}

int	ft_break_redirector(char *str, int pos)
{
	if (str == NULL)
		return (0);
	if (str[pos] != '\0')
	{
		if (str[pos] == ' ' || str[pos] == '>'
			|| str[pos] == '<' || str[pos] == '|')
			return (1);
	}
	return (0);
}

int	ft_its_a_builtins(char *line)
{
	if (line == NULL || ft_strlen(line) <= 0 || ft_strlen(line) > 6)
		return (0);
	if (ft_strlen(line) == 2 && ft_strnstr(line, "cd", 2) != NULL)
		return (1);
	else if (ft_strlen(line) == 3 && (ft_strnstr(line, "env", 3) != NULL
			|| ft_strnstr(line, "pwd", 3) != NULL))
		return (1);
	else if (ft_strlen(line) == 4 && (ft_strnstr(line, "echo", 4) != NULL
			|| ft_strnstr(line, "exit", 4) != NULL))
		return (1);
	else if (ft_strlen(line) == 5 && ft_strnstr(line, "unset", 5) != NULL)
		return (1);
	else if (ft_strlen(line) == 6 && ft_strnstr(line, "export", 6) != NULL)
		return (1);
	else
		return (0);
}

void	ft_print_error(char **line, int *index)
{
	char	*aux;

	g_data.error.error += 1;
	if ((*index > 0 && line[*index] == NULL) || (line[*index] != NULL
			&& ft_its_a_redirector(line[*index],
				ft_strlen(line[*index])) == 1))
		*index -= 1;
	if (line[*index] != NULL && ft_strlen(line[*index]) == 1
		&& line[*index][0] == '~')
		aux = ft_strdup(getenv("HOME"));
	else
		aux = ft_strdup(line[*index]);
	while (line[*index] != NULL)
	{
		if (line[*index] != NULL && ft_its_a_redirector(line[*index],
				ft_strlen(line[*index])) == 1)
		{
			ft_redirector(line, index);
			break ;
		}
		*index += 1;
	}
	ft_send_to_parent("127", aux);
	exit(1);
}

static void	ft_send_to_parent(char *value, char *aux)
{
	if (g_data.exit_status != NULL)
		free(g_data.exit_status);
	g_data.exit_status = ft_strdup(value);
	printf("Minishell: %s: command not found\n", aux);
	if (g_data.pid == 0)
	{
		close(g_data.pipe[0]);
		ft_putstr_fd("?;", g_data.pipe[1]);
		ft_putstr_fd(g_data.exit_status, g_data.pipe[1]);
	}
	ft_clear_struct();
	ft_close_default_fd();
	free(aux);
}
