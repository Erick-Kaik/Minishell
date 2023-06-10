/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:55:50 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/06 15:56:36 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lenth_split(char *str, int *i)
{
	int	x;
	int	len;
	int	quotes;

	len = 0;
	x = 0;
	quotes = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		*i += 1;
	while (str[*i + x] != '\0')
	{
		if (quotes == 0 && ft_break_redirector(str, (*i + x)) == 1)
			return (ft_len_redirector(str, (*i + x), len));
		else if ((str[*i + x] == 34 || str[*i + x] == 39) && quotes == 0)
			quotes = str[*i + x];
		else if (quotes > 0 && str[*i + x] == quotes)
			quotes = 0;
		else if (quotes != 39 && str[*i + x] == '$')
			len += ft_strlen(ft_check_var(str, *i, &x));
		else
			len++;
		x++;
	}
	return (len);
}

int	ft_len_redirector(char *str, int index, int len_backup)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (len_backup > 0)
		return (len_backup);
	while (str[index + i] != ' ' && ft_break_redirector(str, index + i) == 1)
	{
		len++;
		i++;
	}
	return (len);
}

int	ft_count_split(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_break_redirector(str, i) == 1)
			i++;
		else
		{
			count++;
			while (str[i] != '\0' && ft_break_redirector(str, i) == 0)
			{
				if (str[i] == 34 || str[i] == 39)
					i += ft_jump_quotes(str, str[i], i);
				i++;
			}
		}
	}
	count += ft_split_redirection(str);
	return (count);
}

int	ft_split_redirection(char *str)
{
	int	i;
	int	add;

	i = 0;
	add = 0;
	while (str[i] != '\0')
	{
		if (ft_break_redirector(str, i) == 1 && str[i] != ' ' && str[i] != ' ')
		{
			if (str[i + 1] != '\0' && ((str[i] == '>' && str[i + 1] == '>')
					|| (str[i] == '<' && str[i + 1] == '<')))
				i += 2;
			else
				i++;
			add++;
		}
		else
			i++;
	}
	return (add);
}

int	ft_jump_quotes(char *str, char quote, int i)
{
	int	x;

	x = 0;
	if (str[i + x] != '\0' && str[i + x] == quote)
		x++;
	while (str[i + x] != '\0' && str[i + x] != quote)
		x++;
	return (x);
}
