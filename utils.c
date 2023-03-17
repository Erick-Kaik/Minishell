/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:42:52 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/17 16:30:57 by ekaik-ne         ###   ########.fr       */
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
}

void ft_check_line(char *line)
{
    int index;
    char **broke_line;
    
    index = 0;
    getcwd(g_data.path_comand, sizeof(g_data.path_comand));
    add_history(line);
    broke_line = ft_broke_line(line);
    while (broke_line[index] != NULL) // somente printar se for erro, o print tem q ser a ultima coisa
    {
        if (ft_its_a_redirector(broke_line[index]) >= 1)
            ft_redirector(broke_line, &index);
        else if (ft_its_a_builtins(broke_line[index]) == 1) // se for uma builtins alem de retornar 1, ja preenche a struct,
            ft_builtins(broke_line, &index);
        else if (ft_execute_ft_system(broke_line, &index) != -1) //se rodar retorna 1, caso contraio cai no else de erro
            continue; 
        else
            ft_print_error(broke_line, &index);
    }   
}

char **ft_broke_line(char *line) //fazer um tratamento, caso haja aspas (duplas ou simples) tem q tratar tudo q esta dentro
{                               // como um indice do tempo, oq estiver fora pode ser no split msm
    char *aux;
    char **temp;

    aux = ft_strtrim(line, " ");
/*     if (ft_)
        aux = 
    else if ()
        aux = 
    else
        temp = ft_split(aux, ' '); */
    //Ou fazer um ft_count para a qtd de strings q terão, dps ir preenchendo via loop, e coloca a regra das aspas, ja no meio, alem de tratar os $
    temp = ft_split(aux, ' ');
    free(aux);
    return (temp);
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

/* int ft_its_a_builtins(char *line)
{
    ft_assign_to_struct();
} */

/*     int x;
    char *line_t;
    char *first_word;

    x = 0;
    first_word = NULL;
    line_t = ft_strtrim(line, " ");
    while (line_t[x] != '\0')
    {
        if (line_t[x] == ' ' || line_t[x] == '  '
            || line_t[x] == '>' || line_t[x] == '<') 
            break;
        x++;
    }
    first_word = malloc(sizeof(char *) * x);
    ft_memmove(first_word, line_t, x); */