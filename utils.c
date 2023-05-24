/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:42:52 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 16:41:02 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_clear_struct(void)
{
    g_data.fd = 0;
    if (g_data.env.env > 0)
        ft_clear_env();
    if (g_data.pwd.pdw > 0)
        ft_clear_pwd(); 
    if (g_data.echo.echo > 0)
        ft_clear_echo();
}

void ft_starting_variables(char **envp)
{
    g_data.envp = envp;
    ft_add_lst_var(&g_data.var, ft_new_lst_var("?", "0"));
    ft_set_envp_t_var(envp);
}

void ft_set_envp_t_var(char **envp)
{
    int index;
    char **aux;

    index = 0;
    while (envp[index++] != NULL)
    {
        aux = ft_split(envp[index], '=');
        if (aux == NULL)
            break;
        if (g_data.var == NULL)
            g_data.var = ft_new_lst_var(aux[0], aux[1]);
        else
            ft_add_lst_var(&g_data.var, ft_new_lst_var(aux[0], aux[1]));
        free(aux);
    }
}

void ft_get_folder(void)
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
    ft_putstr_fd(temp, 0);
    free(temp);
    ft_clear_split_line(folder);
}

void ft_check_line(char *line)
{
    int index;
    char **broke_line;
    
    index = 0;
    getcwd(g_data.path_comand, sizeof(g_data.path_comand));
    broke_line = ft_broke_line(line);
    while (broke_line[index] != NULL)
    {
        if (ft_its_a_redirector(broke_line[index],
            ft_strlen(broke_line[index])) >= 1)
            ft_redirector(broke_line, &index);
        else if (ft_its_a_builtins(broke_line[index]) == 1)
            ft_builtins(broke_line, &index);
        else if (ft_execute_ft_system(broke_line, &index) != -1)
            continue; 
        else
            ft_print_error(broke_line, &index);
    }
    if (broke_line != NULL)
        ft_clear_split_line(broke_line);
}

void ft_clear_split_line(char **str)
{
    int index;

    index = 0;
    while (str[index] != NULL)
    {
        free(str[index]);
        index++;
    }
    if (str != NULL)
        free(str);
}

void ft_builtins(char **line, int *index)
{
    char *aux;

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