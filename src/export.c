/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:55:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/10 18:01:35 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_send_to_parent(char *name, char *value);

void	ft_export(char **line, int *index)
{
	g_data.exit_status = ft_strdup("1");
	if (line[*index + 1] != NULL && ft_strchr(line[*index + 1], '=') != NULL)
		*index += 1;
	else if (line[*index + 1] == NULL
		|| ft_strchr(line[*index + 1], '=') == NULL)
	{
		while (line[*index] != NULL && ft_strchr(line[*index], '=') == NULL)
			*index += 1;
		while (line[*index] != NULL)
		{
			ft_printf("-Minishell: export: '%s'", line[*index]);
			ft_printf(": not a valid identifier\n");
			*index += 1;
			if (line[*index] == NULL)
				break ;
		}
		return ;
	}
	if (ft_check_name_var(line[*index]) == 1)
		return ;
	ft_adding_export(line, index);
	ft_clear_env();
	while (line[*index] != NULL && ft_its_a_builtins(line[*index]) == 0
		&& g_data.pid == 0)
		*index += 1;
}

void	ft_adding_export(char **line, int *index)
{
	int		x;
	char	**aux;
	char	*name;
	char	*value;

	x = 0;
	aux = ft_split(line[*index], '=');
	value = "";
	while (aux[x] != NULL)
	{
		if (x == 0)
			name = ft_strdup(aux[x]);
		else if (x == 1)
			value = ft_strjoin(value, aux[x]);
		else
		{
			value = ft_strjoin_mod(value, "=");
			value = ft_strjoin_mod(value, aux[x]);
		}
		x++;
	}
	ft_add_lst_var(&g_data.var, ft_new_lst_var(name, value));
	ft_send_to_parent(name, value);
	ft_clear_split_line(aux);
	free(aux);
}

int	ft_check_name_var(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) && str[i] != '=' && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_send_to_parent(char *name, char *value)
{
	if (g_data.exit_status != NULL)
		free(g_data.exit_status);
	g_data.exit_status = ft_strdup("0");
	if (g_data.pid == 0)
	{
		close(g_data.pipe[0]);
		ft_putstr_fd("export:", g_data.pipe[1]);
		ft_putstr_fd(name, g_data.pipe[1]);
		ft_putstr_fd("=", g_data.pipe[1]);
		ft_putstr_fd(value, g_data.pipe[1]);
	}
}
