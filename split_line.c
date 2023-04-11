/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:36:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/04/10 20:20:14 by ekaik-ne         ###   ########.fr       */
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
    add_history(aux);
    count = ft_count_split(line);
    temp = (char **)malloc(sizeof(char *) * (count + 1));
    temp = ft_split_words(aux, temp, count);
/*     // temp = super função pra cortar tudo
    count = ft_count_split(line);
    temp = (char **)malloc(sizeof(char *) * (count + 1));
    temp = ft_split_words(aux, temp, count); */

    // temp = ft_split(aux, ' ');
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
        len = ft_lenth_split(str, &i);
        ft_printf("len = %d\n", len);
        split[index] = (char *)malloc(sizeof(char) * len);
        ft_fill_split(split[index], str, i, len);
        split[index][len] = '\0';
        i += ft_fix_index_position(str, i);
        index++;
    }
    split[index] = NULL;
    return (split);
}

int ft_fix_index_position(char *str, int i)
{
    int x;

    x = 0;
    while (str[i + x] == ' ' && str[i + x] != '\0')
        x++;
    while (str[i + x] != '\0')
    {
        if (str[i + x] == ' ')
            break;
        else if (str[i + x] == 34 || str[i + x] == 39)
            x = ft_jump_quotes(str, str[i + x], (i + x));
        x++;
    }
    return (x);
}

void ft_fill_split(char *dest, char *str, int start, int len)
{
    int i;
    int i_dest;

    i = 0;
    i_dest = 0;
    while (i < len && str[start + i] != '\0')
    {
        if (str[start + i] == ' ')
            break ;
        else if (str[start + i] == '$')
        {
            i_dest += ft_link_var_in_split(dest, ft_check_var(str, start, &i), i_dest);
            if (str[start + i] == ' ')
                break;
        }
        else
            dest[i_dest++] = str[start + i];
        i++;
    }
    
}

int ft_link_var_in_split(char *dest, char* var, int i)
{
    int x;
    
    x = 0;
    while (var[x] != '\0')
    {
        dest[i + x] = var[x];
        x++;
    }
    return (x);
}

int ft_lenth_split(char *str, int *i)
{
    int x;
    int len;
    int quotes;

    len = 0;
    x = 0;
    quotes = 0;
    while (str[*i] == ' ' && str[*i] != '\0')
        *i += 1;
    while (str[*i + x] != '\0')
    {
        if (quotes == 0 && str[*i + x] == ' ')
            break;
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

int ft_len_quotes(char *str, char quote, int i)
{
    int x;
    int len;

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
    if (temp == NULL)
        ft_sig_close(0);
    aux = ft_strtrim(temp, " ");
    free(temp);
    aux = ft_strjoin_mod(aux, "\n");
    add_history(aux);
    if (line[ft_strlen(line) - 1] != '\n')
        line = ft_strjoin_mod(line, "\n");
    line = ft_strjoin_mod(line, aux);

    return (line);
}

char *ft_check_var(char *str, int i, int *index)
{
    int x;
    int len;
    char *aux;
    char *temp;

    x = i + *index;
    len = 0;
    if (str[x] == '$')
        x++;
    while (str[x] != '\0' && (ft_isalnum(str[x]) == 1
        || str[x] == '_'))
    {
        x++;
        len++;
    }
    aux = malloc(sizeof(char *) * len + 1);
    ft_strlcpy(aux, &str[i + *index + 1], len + 1);
    temp = ft_get_var(aux);
    *index += ft_strlen(aux) + 1;
    free(aux);
    return (temp);
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
    return (NULL);
}
/*
1° ft -> conta quantas linhas vao ter nas Char**
2° ft -> aplica o conteudo de str na linha splitada, assim fnzd o tratamento (cria o malloc fora da 1 e da 2)

//split somente entre espacos e tudo dentro das aspas é 1 coias so
 */