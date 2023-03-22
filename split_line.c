/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:36:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/22 17:15:45 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_broke_line(char *line) //fazer um tratamento, caso haja aspas (duplas ou simples) tem q tratar tudo q esta dentro
{                               // como um indice do tempo, oq estiver fora pode ser no split msm
    int count;
    char *aux;
    char **temp;

    aux = ft_strtrim(line, " ");
    while (ft_open_quotes(aux) == 1)
        aux = ft_get_more_content(aux);
    // temp = super função pra cortar tudo
    count = ft_count_split(line);
    // temp = (char **)malloc(sizeof(char *) * (index + 1));
    temp = ft_split_words(aux, temp, count);

    temp = ft_split(aux, ' ');
    free(aux);
    return (temp);
}

char **ft_split_words(char *str, char **split, int count)
{
    int i;
    int len;
    int index;

    i = 0;
    index = 0;
    while (index < count)
    {
        len = 0;
        len = ft_lenth_split(str, &i);
        split[index] = (char *)malloc(sizeof(char) * (len + 1));

    }
    return (NULL);
}

int ft_lenth_split(char *str, int *i)
{
    int len;
    int sub;

    len = 0;
    sub = 0;
    while (str[*i] == ' ' && str[*i] != '\0')
        *i += 1;
    while (str[*i + len] != '\0')
    {
        if (str[*i + len] == ' ')
            break;
        else if (str[*i + len] == 34 || str[*i + len] == 39)
        {
            len += ft_jump_quotes(str, str[*i + len], (*i + len));
            sub++;
        }
        else if (str[*i + len] == '$')
            len += ;
    }
    if (sub > 0)
        len -= (sub * 2);
    return (len);
}

int ft_count_split(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ')
            i++;
        else
        {
            count++;
            while (str[i] != '\0' && str[i] != ' ')
            {
                if (str[i] == 34 || str[i] == 39)
                    i += ft_jump_quotes(str, str[i], i);
                i++;
            }
        }
    }
    return (count);
}

int ft_jump_quotes(char *str, char quote, int i)
{
    int x;
    
    x = 0;
    if (str[i + x] != '\0' && str[i + x] == quote)
        x++;
    while (str[i + x] != '\0' && str[i + x] != quote)
        x++;
    return (x);
}

int ft_open_quotes(char *line)
{
    int i;
    int quote;
    int count;

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

char *ft_get_more_content(char *line)
{
    char *aux;
    char *temp;
	rl_on_new_line();
    temp = readline("> ");
    aux = ft_strtrim(temp, " ");
    free(temp);
    aux = ft_strjoin_mod(aux, "\n");
    line = ft_strjoin_mod(line, aux);
    return (line);
}

char *ft_check_var(char *str, int *i)
{
    int x;
    int len;
    char *aux;

    x = 0;
    len = 0;
    if (str[*i + x] == '$')
        x++;
    while (str[*i + x] != '\0' && (ft_isalnum(str[*i + x]) == 1
        || str[*i + x] == '_'))
        x++;
    aux = malloc(sizeof(char *) * x + 1);
    x = 0;
    while (str[*i + x + 1] != '\0' && (ft_isalnum(str[*i + x + 1]) == 1
        || str[*i + x + 1] == '_'))
        aux[x] = str[*i + x++ + 1];
    aux[x] = '\0';
    return (ft_get_var(aux));
}

char *ft_get_var(char *name_var)
{
    t_var *aux;

    aux = g_data.var;
    while (aux != NULL)
    {
        if (ft_strncmp(aux->name, name_var, ft_strlen(aux->name)) == 0)
            return (aux->content);
        aux = aux->next;
    }
    return (name_var);
}

/*
1° ft -> conta quantas linhas vao ter nas Char**
2° ft -> aplica o conteudo de str na linha splitada, assim fnzd o tratamento (cria o malloc fora da 1 e da 2)

//split somente entre espacos e tudo dentro das aspas é 1 coias so
 */