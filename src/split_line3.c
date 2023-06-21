/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucdos-s <lukas.facchi@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:55:54 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/08 11:08:37 by lucdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_quotes(char *str, char quote, int i)
{
	int	x;
	int	len;

	x = 0;
	len = 0;
	if (str[i + x] != '\0' && str[i + x] == quote)
		x++;
	while (str[i + x] != '\0' && str[i + x] != quote)
	{
		if (quote == 34 && str[i + x] == '$')
			len += (int)ft_strlen(ft_check_var(str, i, &x));
		else
			len++;
		x++;
	}
	return (len);
}

int	ft_open_quotes(char *line)
{
	int	i;
	int	quote;
	int	count;

	i = 0;
	quote = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == 34 || line[i] == 39) && quote == 0)
		{
			quote = line[i];
			count++;
		}
		else if (quote > 0 && line[i] == quote)
		{
			quote = 0;
			count++;
		}
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

char	*ft_get_more_content(char *line, int *concat)
{
	char	*aux;
	char	*temp;

	rl_on_new_line();
	temp = readline("> ");
	if (temp == NULL)
	{
		ft_printf("-Minishell: unexpected EOF while looking");
		ft_printf("for matching '%c'\n", ft_get_quote_open(line));
		ft_printf("-Minishell: syntax error: unexpected end of file\n");
		free(line);
		return (NULL);
	}
	aux = ft_strtrim(temp, " ");
	free(temp);
	if (line[ft_strlen(line) - 1] != '|')
		line = ft_strjoin_mod(line, "\n");
	line = ft_strjoin_mod(line, aux);
	free(aux);
	*concat += 1;
	return (line);
}

char	*ft_check_var(char *str, int i, int *index)
{
	int		x;
	int		len;
	char	*aux;
	char	*temp;

	x = i + *index;
	len = 0;
	if (str[x] == '$')
		x++;
	while (str[x] != '\0'
		&& (ft_isalnum(str[x]) == 1 || str[x] == '?' || str[x] == '_'))
	{
		x++;
		len++;
	}
	if (len == 0)
		return ("$");
	aux = malloc(sizeof(char *) * len + 1);
	ft_strlcpy(aux, &str[i + *index + 1], len + 1);
	temp = ft_get_var(aux);
	*index += len;
	free(aux);
	return (temp);
}

char	*ft_get_var(char *name_var)
{
	t_var	*aux;

	aux = g_data.var;
	while (aux != NULL)
	{
		if (ft_strlen(aux->name) == ft_strlen(name_var))
			if (ft_strncmp(aux->name, name_var, ft_strlen(aux->name)) == 0)
				return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}
