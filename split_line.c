/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:36:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 16:41:28 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_broke_line(char *line)
{
	int		count;
	char	*aux;
	char	**temp;

	temp = NULL;
	aux = ft_strtrim(line, " ");
	count = ft_count_split(aux);
	temp = (char **)malloc(sizeof(char *) * (count + 1));
	temp = ft_split_words(aux, temp, count);
	free(aux);
	return (temp);
}

char	**ft_split_words(char *str, char **split, int count)
{
	int	i;
	int	len;
	int	index;

	i = 0;
	index = 0;
	while (index < count)
	{
		len = ft_lenth_split(str, &i);
		split[index] = (char *)malloc(sizeof(char) * len + 1);
		ft_fill_split(split[index], str, i, len);
		split[index][len] = '\0';
		i += ft_fix_index_position(str, i);
		index++;
	}
	split[index] = NULL;
	return (split);
}

int	ft_fix_index_position(char *str, int i)
{
	int		x;
	char	c_red;

	x = 0;
	if (ft_break_redirector(str, i) == 1)
		c_red = str[i];
	else
		c_red = '\0';
	while ((str[i + x] == ' ' || (c_red != '\0' && str[i + x] == c_red))
		&& str[i + x] != '\0')
		x++;
	while (str[i + x] != '\0' && c_red == '\0')
	{
		if (ft_break_redirector(str, (i + x)) == 1)
			break ;
		else if (str[i + x] == 34 || str[i + x] == 39)
			x += ft_jump_quotes(str, str[i + x], (i + x));
		x++;
	}
	return (x);
}

void	ft_fill_split(char *dest, char *str, int start, int len)
{
	int	i;
	int	quotes;
	int	i_dest;

	i = 0;
	i_dest = 0;
	quotes = 0;
	while (i_dest < len && str[start + i] != '\0')
	{
		if (quotes == 0 && str[start + i] == 32)
			break ;
		else if (str[start + i] == '$' && quotes != 39)
		{
			i_dest += ft_link_var(dest, ft_check_var(str, start, &i), i_dest);
			if (str[start + i] == ' ')
				continue ;
		}
		else if (str[start + i] == 39 || str[start + i] == 34)
			quotes = str[start + i];
		else if (quotes > 0 && str[start + i] == quotes)
			quotes = 0;
		else
			dest[i_dest++] = str[start + i];
		i++;
	}
}

int	ft_link_var(char *dest, char *var, int i)
{
	int	x;

	x = 0;
	while (var[x] != '\0')
	{
		dest[i + x] = var[x];
		x++;
	}
	return (x);
}
