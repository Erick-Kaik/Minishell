/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:02:10 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/10 09:24:52 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_read_comand(char *str, t_var **var, t_history **history)
{
    add_history(str);
	//ft_add_history(str, history);
    if (ft_strnstr(str, "cd", ft_strlen(str)) != NULL)
        ft_cd(ft_strnstr(str, "cd", ft_strlen(str)), var);
    else if (ft_strnstr(str, "echo", ft_strlen(str)) != NULL) // ->
        ft_echo(ft_strnstr(str, "echo", ft_strlen(str)), var);
    else if (ft_strnstr(str, "pwd", ft_strlen(str)) != NULL) // ->
        ft_pwd(ft_strnstr(str, "pwd", ft_strlen(str)), var);
    else if (ft_strnstr(str, "env", ft_strlen(str)) != NULL) // ->
        ft_env(ft_strnstr(str, "env", ft_strlen(str)), var);
    else if (ft_strnstr(str, "export", ft_strlen(str)) != NULL)
        ft_export(ft_strnstr(str, "export", ft_strlen(str)), var);
    else if (ft_strnstr(str, "unset", ft_strlen(str)) != NULL)
        ft_unset(ft_strnstr(str, "unset", ft_strlen(str)), var);
    else if (ft_strnstr(str, "exit", ft_strlen(str)) != NULL) // printa exit e cria o file e dps  fecha
        ft_exit();
    else if (ft_strnstr(str, "$?", ft_strlen(str)) != NULL)
        ft_vl_last_comand(var, 1);
    else if (ft_strnstr(str, "history", ft_strlen(str)) != NULL) // -> apagar q n é buildint
        ft_history(ft_strnstr(str, "history", ft_strlen(str)), *history, var);
}

char *ft_jump_spaces(char const *str, char *comand)
{
	int		x;
	int		y;
	char	*txt;
	char	*path;

	y = 0;
	x = ft_strlen(comand);
	txt = ft_strnstr(str, comand, ft_strlen(str));
	while ((txt[x] == ' ' || txt[x] == '	') && txt[x] != '\0')
		x++;
	path = malloc(sizeof(char *) * (ft_strlen(txt) - x - 1));
	if (path == NULL)
		return (NULL);
	while (txt[x] != '\n' && txt[x] != '\0')
		path[y++] = txt[x++];
	path[y] = '\0';
	return (path);
}

char *ft_get_var(char *str)
{
	int		x;
	int		y;
	char	*temp;
	char	*var;

	x = 0;
	y = 0;
	var = NULL;
	temp = ft_strnstr(str, "$", ft_strlen(str));
	if (temp != NULL)
	{
		while (temp[x + 1] != 32 && temp[x + 1] != 9
			&& temp[x + 1] != '\0' && temp[x + 1] != '\n')
			x++;
		var = malloc(sizeof(char *) * x);
		x = 1;
		while (temp[x] != 32 && temp[x] != 11
			&& temp[x] != '\0' && temp[x] != '\n')
			var[y++] = temp[x++];
		var[y] = '\0';
	}
	return (var);
}

char *ft_get_folder(void)
{
    char str[PATH_MAX];
	char **folder;
    char *temp;
    int x;

	x = 0;
	folder = NULL;
    temp = ft_strjoin(getenv("USER"), ":~/");
    if (getcwd(str, sizeof(str)) != NULL)
    {
        if (ft_strlen(str) > 1)
		{
			folder = ft_split(str, '/');
			while (folder[x] != NULL)
				x++;
            temp = ft_strjoin_mod(temp, folder[x - 1]);
		}
    }
    temp = ft_strjoin_mod(temp, "$->");
    return (temp);
}

void ft_exit()
{
	t_var *var;
	t_history *history;

	var = ft_create_and_send_var(0, NULL);
	history = ft_create_and_send_history(0);
	
	ft_clear_var(&var, ft_del_var);
	ft_clear_history(&history, ft_del_history);
	ft_printf("exit\n");
	exit(1);
}

void	ft_add_value_last_com(t_var **var, char *value)
{
	t_var *aux;

	aux = *var;
	while (ft_strlen(aux->name) != 2 && (aux->name[0] != '$' && aux->name[1] != '?'))
		aux = aux->next;
	aux->content = value;
}

