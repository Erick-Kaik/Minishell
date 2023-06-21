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

static void	ft_send_to_parent(char **line, int args);
static char	*ft_get_value_exit(char **line);
static char	*ft_agroup_exit_value(char *value);

void	ft_exit(char **line)
{
	int	pipe;
	int	x;

	x = 0;
	pipe = 0;
	while (line[x] != NULL)
	{
		if (ft_its_a_redirector(line[x], ft_strlen(line[x])) == 1)
		{
			ft_redirector(line, &x);
			if (line[x] == NULL)
				break ;
			else if (ft_strlen(line[x]) == 1 && line[x][0] == '|')
			{
				x++;
				pipe = 1;
			}
		}
		x++;
	}
	if (pipe == 0)
		ft_send_to_parent(line, x);
	ft_clear_struct();
	ft_close_default_fd();
	exit(1);
}

static void	ft_send_to_parent(char **line, int args)
{
	char	*value;

	if (args == 1)
		value = ft_strdup("0");
	else
		value = ft_get_value_exit(line);
	if (ft_atoi(value) == 2)
		ft_putstr_fd("Minishell: exit: numeric argument required\n",
			g_data.original_fd[1]);
	else if (ft_atoi(value) == 2)
		ft_putstr_fd("Minishell: exit: too many arguments\n",
			g_data.original_fd[1]);
	else if (ft_atoi(value) > 255 || ft_atoi(value) < 0)
		value = ft_agroup_exit_value(value);
	if (g_data.pid == 0)
	{
		close(g_data.pipe[0]);
		ft_putstr_fd("exit;", g_data.pipe[1]);
		ft_putstr_fd("?;", g_data.pipe[1]);
		ft_putstr_fd(value, g_data.pipe[1]);
	}
	free(value);
}

void	ft_exit_parent(char **split, char *line, char *input_line)
{
	int		aux;
	t_var	*temp;

	temp = g_data.var;
	while (temp != NULL)
	{
		if (ft_strlen(temp->name) == 1 && temp->name[0] == '?')
			break ;
		temp = temp->next;
	}
	aux = ft_atoi(temp->content);
	printf("logout\n");
	ft_clear_struct();
	ft_clear_split_line(split);
	if (split != NULL)
		free(split);
	free(line);
	free(input_line);
	ft_close_default_fd();
	exit(aux);
}

static char	*ft_get_value_exit(char **line)
{
	int	x;
	int	arg;

	x = -1;
	arg = 0;
	while (line[++x] != NULL)
	{
		if (ft_its_a_redirector(line[x], ft_strlen(line[x])) == 1)
			break ;
		arg++;
	}
	if (ft_strlen(line[0]) == 4 && ft_strnstr(line[0], "exit", 4) != NULL)
		arg--;
	if (arg > 1)
		return (ft_strdup("1"));
	else if (arg <= 0)
		return (ft_strdup("0"));
	x = -1;
	if (ft_strisdigit(line[1]) == 1)
		return (ft_strdup(line[1]));
	else
		return (ft_strdup("2"));
}

static char	*ft_agroup_exit_value(char *value)
{
	int	converter;
	int	new_value;

	converter = 1;
	new_value = ft_atoi(value);
	if (new_value < 0)
		converter *= -1;
	while (new_value < 0 || new_value > 255)
		new_value = new_value - (256 * converter);
	free(value);
	return (ft_itoa(new_value));
}
