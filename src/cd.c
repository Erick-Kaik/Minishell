/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:17:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/12 13:20:52 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_send_to_parent(char *value);
static void	ft_close_by_cd(void);

void	ft_cd(char **line, int *index)
{
	int		value;
	char	*path;
	char	*aux;

	value = 0;
	aux = ft_get_path_cd(line, index);
	if (ft_strlen(aux) == 1 && aux[0] == '~')
		path = ft_strdup(getenv("HOME"));
	else if (ft_strlen(aux) > 1 && aux[0] == '~' && aux[1] == '/')
		path = ft_strjoin(getenv("HOME"), &aux[1]);
	else
		path = ft_strdup(aux);
	value = chdir(path);
	if (g_data.pid == 0 && value >= 0 && path != NULL)
		ft_send_to_parent(aux);
	free(aux);
	if (value == -1)
		ft_printf("Minishell: %s: '%s': No such file or directory\n",
			line[*index], line[*index + 1]);
	if (path != NULL)
		free(path);
	while (line[*index] != NULL && ft_its_a_redirector(line[*index],
			ft_strlen(line[*index])) == 0 && g_data.pid == 0)
		*index += 1;
}

char	*ft_get_path_cd(char **line, int *index)
{
	char	*path;

	path = NULL;
	if (g_data.exit_status != NULL)
		free(g_data.exit_status);
	if (g_data.pid == 0)
		g_data.exit_status = ft_strdup("1");
	if (line[*index + 1] == NULL || (line[*index + 1] != NULL
			&& ft_its_a_redirector(line[*index + 1],
				ft_strlen(line[*index + 1])) == 1))
		path = ft_strdup("~");
	else if (line[*index + 1] != NULL && ft_its_a_redirector(line[*index + 1],
			ft_strlen(line[*index + 1])) == 0)
	{
		if (line[*index + 2] != NULL && ft_its_a_redirector(line[*index + 2],
				ft_strlen(line[*index + 2])) == 0 && g_data.pid == 0)
			ft_printf("Minishell: %s: too many arguments\n", line[*index]);
		else
			path = ft_strjoin(path, line[*index + 1]);
	}
	if (path == NULL)
		ft_close_by_cd();
	return (path);
}

static void	ft_send_to_parent(char *value)
{
	if (g_data.exit_status != NULL)
		free(g_data.exit_status);
	if (g_data.pid == 0)
	{
		g_data.exit_status = ft_strdup("0");
		close(g_data.pipe[0]);
		ft_putstr_fd("cd;", g_data.pipe[1]);
		ft_putstr_fd(value, g_data.pipe[1]);
	}
}

static void	ft_close_by_cd(void)
{
	if (close(g_data.pipe[0]) == -1)
		ft_putstr_fd(";", g_data.pipe[1]);
	ft_putstr_fd("?;", g_data.pipe[1]);
	ft_putstr_fd(g_data.exit_status, g_data.pipe[1]);
	ft_clear_struct();
	ft_close_default_fd();
	exit(1);
}
