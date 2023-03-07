/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:27:49 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 17:54:40 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char *txt, t_var **var)
{
	int x;
	int fd;
	char *str;

	x = 0;
	str = ft_check_echo(txt, &fd, var);
	if (str == NULL)
		return ;
	while (str[x] != '\0')
	{
		if (str[x] == 39) // simples
			x += ft_single_quote(x, str, fd);
		else if (str[x] == 34) // duplas
			x += ft_double_quote(x, str, fd, var);
		else if (str[x] == '$')
			x += ft_check_variable(x, str, fd, var);
		ft_putchar_fd(str[x], fd);
		x++;
	}
	if (ft_strnstr(txt, "-n", ft_strlen(txt)) == NULL && fd >= 0)
		ft_putchar_fd('\n', fd);
	ft_add_value_last_com(var, "0");
}

char *ft_check_echo(char *txt, int *fd, t_var **var)
{
	char *str;

	if (ft_strnstr(txt, "-n", ft_strlen(txt)) != NULL)
		str = ft_jump_spaces(ft_strtrim(txt, "\n"), "-n");
	else
		str = ft_jump_spaces(ft_strtrim(txt, "\n"), "echo");
	if (str != NULL && ft_check_two_quotes(str, var) == -1)
		return (NULL);
	if (str == NULL)
		return (NULL);
	*fd = ft_check_redirector(str);
	if (fd > 0)
		str = ft_str_echo(str);
	return (str);
}

char *ft_str_echo(char *str)
{
	int		x;
	int		y;
	char	*print;

	x = 0;
	y = 0;
	while (str[x] != '\0' && str[x + 1] != '>' && str[x + 1] != '<')
		x++;
	print = malloc(sizeof(char *) * x);
	while (y < x)
	{
		print[y] = str[y];
		y++;
	}
	print[y] = '\0';
	return (print);
}

int ft_check_redirector(char *str)
{
	int x;
	int fd;

	x = 0;
	fd = 0;
	while (str[x] != '\0' && fd == 0)
	{
		if (str[x] == '<')
		{
			if (str[x + 1] == '<')
				fd = ft_rd_loop_input(str);
			else
				fd = ft_rd_input(str);
		}
		else if (str[x] == '>')
		{
			if (str[x + 1] == '>')
				fd = ft_rd_last_output(str);
			else
				fd = ft_rd_output(str);
		}
		x++;
	}
	return (fd);
}

int ft_check_two_quotes(char *str, t_var **var)
{
	int x;
	int quotes[2];

	x = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str[x] != '\0')
	{
		if ((str[x] == 34 || str[x] == 39) && quotes[1] == 0)
		{
			quotes[0] = str[x];
			quotes[1]++;
		}
		else if (quotes[1] > 0 && str[x] == quotes[0])
			quotes[1] = 0;
		x++;
	}
	if (quotes[1] > 0)
	{
		ft_add_value_last_com(var, "127");
		ft_printf("syntax error\n");
		return (-1);
	}
	else
		return (0);
}

int ft_single_quote(int pos, char *str, int fd)
{
	int x;
	int quotes;

	x = 0;
	quotes = 0;
	if (str[pos] == 39)
	{
		quotes = 1;
		x++;
	}
	while (str[pos + x] != '\0' && quotes < 2)
	{
		if (str[pos + x] == 39)
			quotes++;
		if (quotes < 2)
			ft_putchar_fd(str[pos + x], fd);
		x++;
	}
	return (x);
}

int ft_double_quote(int pos, char *str, int fd, t_var **var)
{
	int x;
	int quotes;

	x = 0;
	quotes = 0;
	if (str[pos] == 34)
	{
		quotes = 1;
		x++;
	}
	while (str[pos + x] != '\0' && quotes < 2)
	{
		if (str[pos + x] == 34)
			quotes++;
		if (str[pos + x] == '$')
			x += ft_check_variable(pos + x, str, fd, var);
		if (quotes < 2)
			ft_putchar_fd(str[pos + x], fd);
		x++;
	}
	return (x);
}

int ft_check_variable(int pos, char *str, int fd, t_var **var)
{
	size_t len;
	char *var_amb;
	char *result;
	
	len = 0; 
	if (str[pos] == '$')
	{
		var_amb = ft_get_var(&str[pos]);
		if (var_amb[0] == '?')
			return (ft_echo_last_comand(var, fd) + 1);
		result = ft_print_var(*var, var_amb);
		if (result == NULL)
			return (0);
		ft_putstr_fd(result, fd);
		if (ft_strlen(result) == 1 && result[0] != '\n')
			free(result);
		len = ft_strlen(var_amb);
		free(var_amb);
	}
	return (len + 1);
}

int ft_echo_last_comand(t_var **var, int fd)
{
	t_var	*aux;
	size_t	len;

	aux = *var;
	len = 0;
	while (ft_strlen(aux->name) != 2 && (aux->name[0] != '$' && aux->name[1] != '?'))
		aux = aux->next;
	while (len < ft_strlen(aux->content))
		ft_putchar_fd(aux->content[len++], fd);
	ft_vl_last_comand(var, 0);
	len = ft_strlen(aux->content);
	return (len);
}

void ft_vl_last_comand(t_var **var, int solo)
{
	t_var *aux;

	aux = *var;
	if (solo == 1)
	{
		while (ft_strlen(aux->name) != 2 && (aux->name[0] != '$' && aux->name[1] != '?'))
			aux = aux->next;
		ft_printf("bash: %s: command not found\n", aux->content);
		ft_add_value_last_com(var, "127");
	}
	else
		ft_add_value_last_com(var, "0");
}

char *ft_print_var(t_var *var, char *amb)
{
	char *result;
	char *str;
	t_var *aux;

	aux = var;
	result = NULL;
	str = ft_filter_str_amb(amb);
	while (aux != NULL)
	{
		if (ft_strncmp(aux->name, str, ft_strlen(aux->name)) == 0)
		{
			result = aux->content;
			break;
		}
		aux = aux->next;
	}
	if (result == NULL)
		result = ft_rest_of_str_amb(str, amb);
	if (str != NULL)
		free(str);
	return (result);
}

char *ft_filter_str_amb(char *amb)
{
	char *temp;
	int len;
	int x;

	len = 0;
	x = 0;
	while (amb[len] != '\0' && (ft_isalpha(amb[len]) == 1 || amb[len] == '_'))
		len++;
	temp = malloc(sizeof(char) * len);
	if (temp == NULL)
		return (NULL);	
	while (x < len)
	{
		temp[x] = amb[x];
		x++;
	}
	temp[x] = '\0';
	return (temp);
}

char *ft_rest_of_str_amb(char *filter, char *amb)
{
	size_t len_amb;
	size_t len_fil;
	size_t len;
	char *temp;

	len_amb = ft_strlen(amb);
	len_fil = ft_strlen(filter);
	temp = NULL;
	len = 0;
	if (len_fil == len_amb)
		temp = "";
	else if (len_fil < len_amb)
	{

		temp = malloc(sizeof(char) * (len_amb - len_fil));
		while (len_fil < len_amb)
			temp[len++] = amb[len_fil++];
		temp[len_fil] = '\0';
	}
	return (temp);
}
