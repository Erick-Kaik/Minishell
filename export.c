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

void	ft_export(char **line, int *index)
{
	if (line[*index + 1] != NULL && ft_strchr(line[*index + 1], '=') != NULL)
		*index += 1;
	else if (line[*index + 1] == NULL
		|| ft_strchr(line[*index + 1], '=') == NULL)
	{
		*index += 1;
		return ;
	}
	if (ft_check_name_var(line[*index]) == 1)
		return ;
	ft_adding_export(line, index);
	ft_clear_env();
	while (line[*index] != NULL && ft_its_a_builtins(line[*index]) == 0)
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
}

int	ft_check_name_var(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) || str[i] == '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
