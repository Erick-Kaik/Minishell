/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucdos-s <lukas.facchi@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:12:53 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/08 11:37:52 by lucdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_split_line(char **str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return ;
	else if (str[index] == NULL)
		return ;
	while (str[index] != NULL)
	{
		free(str[index]);
		index++;
	}
}

void	ft_builtins(char **line, int *index)
{
	char	*aux;

	aux = line[*index];
	if (ft_strlen(aux) == 2 && ft_strnstr(aux, "cd", 2) != NULL)
		ft_cd(line, index);
	else if (ft_strlen(aux) == 3 && ft_strnstr(aux, "env", 3) != NULL)
		ft_env(line, index);
	else if (ft_strlen(aux) == 3 && ft_strnstr(aux, "pwd", 3) != NULL)
		ft_pwd(line, index);
	else if (ft_strlen(aux) == 4 && ft_strnstr(aux, "echo", 4) != NULL)
		ft_echo(line, index);
	else if (ft_strlen(aux) == 4 && ft_strnstr(aux, "exit", 4) != NULL)
		ft_exit(line);
	else if (ft_strlen(aux) == 5 && ft_strnstr(aux, "unset", 5) != NULL)
		ft_unset(line, index);
	else if (ft_strlen(aux) == 6 && ft_strnstr(aux, "export", 6) != NULL)
		ft_export(line, index);
}

char	*ft_verify_line(void)
{
	char	*line;
	char	*aux;

	aux = ft_get_folder();
	line = readline(aux);
	free (aux);
	if (line == NULL)
	{
		ft_clear_struct();
		exit(1);
	}
	if (ft_strlen_other(line, ' ') <= 0)
	{
		free(line);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return (NULL);
	}
	return (line);
}

char	ft_get_quote_open(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == 34 || line[i] == 39) && quote == 0)
			quote = line[i];
		else if (quote > 0 && line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}
