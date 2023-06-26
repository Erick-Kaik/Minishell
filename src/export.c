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
	*index += 1;
	if (line[*index] == NULL)
	{
		ft_get_print_env(0);
		return ;
	}		
	else if (ft_strchr(line[*index], '=') == NULL)
	{
		while (line[*index] != NULL && (ft_strlen(line[*index]) != 1
				&& line[*index][0] != '?'))
		{
			ft_add_lst_var(&g_data.var, ft_new_lst_var(
					ft_strdup(line[*index]), NULL));
			if (g_data.fd == 0)
				ft_send_to_parent(ft_strdup(line[*index]), NULL);
			*index += 1;
		}
		return ;
	}
	if (ft_check_name_var(line, index, 0) == 1)
		return ;
	ft_adding_export(line, index);
	while (line[*index] != NULL && ft_its_a_builtins(line[*index]) == 0
		&& g_data.pid == 0)
		*index += 1;
}

void	ft_adding_export(char **line, int *index)
{
	int		x;
	char	**aux;
	char	*name;
	char	*vl;

	x = 0;
	aux = ft_split(line[*index], '=');
	vl = ft_strdup("");
	while (aux[x] != NULL)
	{
		if (x == 0)
			name = ft_strdup(aux[x]);
		else if (x == 1)
			vl = ft_strjoin_mod(vl, aux[x]);
		else
		{
			vl = ft_strjoin_mod(vl, "=");
			vl = ft_strjoin_mod(vl, aux[x]);
		}
		x++;
	}
	ft_adding_or_replacing_export(name, vl);
	ft_send_to_parent(name, vl);
	ft_clear_split_line(aux);
	free(aux);
}

int	ft_check_name_var(char **line, int *index, size_t i)
{
	g_data.exit_status = ft_strdup("1");
	if (ft_strlen(line[*index]) < 2 || (ft_isalpha(line[*index][0]) == 0
		&& line[*index][i] != '_') || (ft_strlen(line[*index]) > 1
			&& line[*index][0] == '=') || ft_strrchr(line[*index], '~') != NULL)
	{
		while (line[*index] != NULL)
		{
			ft_printf("-Minishell: export: '%s'", line[*index]);
			ft_printf(": not a valid identifier\n");
			*index += 1;
			if (line[*index] == NULL)
				break ;
		}
		return (1);
	}
	while (i < ft_strlen(line[*index]) && line[*index][i] != '='
		&& line[*index][i] != '\0')
	{
		if (ft_isalnum(line[*index][i]) == 0 && line[*index][i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_send_to_parent(char *name, char *value)
{
	if (g_data.pid == 0)
	{
		if (g_data.exit_status != NULL)
			free(g_data.exit_status);
		g_data.exit_status = ft_strdup("0");
		close(g_data.pipe[0]);
		ft_putstr_fd("export;", g_data.pipe[1]);
		ft_putstr_fd(name, g_data.pipe[1]);
		if (value != NULL)
		{
			ft_putstr_fd("=", g_data.pipe[1]);
			ft_putstr_fd(value, g_data.pipe[1]);
		}
	}
	free(name);
	if (value != NULL)
		free(value);
}

void	ft_adding_or_replacing_export(char *name, char *vl)
{
	t_var	*aux;
	t_var	*temp;

	aux = g_data.var;
	temp = aux;
	if (ft_check_exist_var(name) == 1)
	{
		while (temp != NULL)
		{
			if (ft_strlen(temp->name) == ft_strlen(name) && ft_strncmp(
					temp->name, name, ft_strlen(temp->name)) == 0)
			{
				free(temp->content);
				temp->content = ft_strdup(vl);
				break ;
			}
			temp = temp->next;
		}
		g_data.var = aux;
	}
	else
		ft_add_lst_var(&g_data.var, ft_new_lst_var(ft_strdup(name),
				ft_strdup(vl)));
	ft_clear_env();
}
