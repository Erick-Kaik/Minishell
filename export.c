/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:25:14 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/07 21:40:27 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_export(char *varaible, t_var **var)
{
	char	*title;
	char	*value;
	char	*f_var;

	f_var = ft_jump_spaces(varaible, "export");
	if (ft_check_f_var(f_var) == 1)
		return ;
	ft_apply_title_value(f_var, &title, &value, var);
	if (value != NULL)
		ft_add_lst_var(var, ft_new_lst_var(title, value));
}

void ft_apply_title_value(char *varaible, char **title, char **value, t_var **var)
{
	char **str;

	str = ft_split(varaible, '=');
	ft_format_value(&str[1], var);
	*title = str[0];	
	*value = str[1];
}

void ft_format_value(char **str, t_var **var)
{
	char	*temp;
	int		x;

	temp = *str;
	if (ft_check_two_quotes(temp, var) == -1)
	{
		*str = NULL; 
		return ;
	}
	x = ft_count_temp_to_str(temp, var);
	*str = ft_fill_value_var(temp, x);
}

int ft_count_temp_to_str(char *temp, t_var **var)
{
	int x;
	int y;

	x = 0;
	y = x;
	while (temp[x] != '\0')
	{
		if (temp[x] == '\t' || temp[x] == 32)
		{
			ft_print_error(&temp[x], var);
			break;
		}
		else if (temp[x] == 34 || temp[x] == 39)
		{
			y += ft_format_quotes(&temp[x], temp[x]);
			x += ft_format_quotes(&temp[x], temp[x]) + 2;
		}
		else
			y++;
		x++;
	}
	return (y);
}

int ft_format_quotes(char *str, char quote)
{
	int x;
	int y;
	int c_quote;
	
	x = 0;
	y = x;
	c_quote = 0;
	while (str[x] != '\0' && c_quote < 2)
	{
		if (str[x] != quote)
			y++;
		if (str[x] == quote)
			c_quote++;
		x++;
	}
	return (y);
}

char *ft_fill_value_var(char *temp, int size)
{
	char *aux;
	int x;
	int y;
	int quotes[2];

	x = 0;
	y = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	aux = malloc(sizeof(char) * size + 1);
	while (temp[x] != '\0')
	{
		if (quotes[1]++ == 0 && (temp[x] == 34 || temp[x] == 39))
			quotes[0] = temp[x];
		else if (quotes[1]-- == 1 && temp[x] == quotes[0])
			quotes[0] = 0;
		else
			aux[y++] = temp[x];
		x++;
	}
	aux[y] = '\0';
	return (aux);
}

void ft_print_error(char *str, t_var **var)
{
	char **bash_errors;
	int x;

	x = 0;
	bash_errors = ft_split(str, ' ');
	while (bash_errors[x] != NULL)
	{
		ft_printf("-bash: export: '%s': not a valid identifier\n", bash_errors[x]);
		x++;
	}
	ft_add_value_last_com(var, "1");
}

int ft_check_f_var(char *str)
{
	int x;
	int equals;
	int error;

	x = 0;
	equals = 0;
	error = 0;
	if (ft_isalpha(str[0]) == 0)
		error++;
	while (str[x] != '\0')
	{
		if (str[x] == '=')
			equals++;
		if (equals == 0 && ft_isalnum(str[x]) == 0)
			error++;
		x++;
	}
	if (error > 0)
		ft_printf("Error in sintaxy!\n");		
	if (equals == 0 || error > 0)
		return (1);
	return(0);
}
