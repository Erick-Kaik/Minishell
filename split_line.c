/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:36:41 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/17 17:55:35 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
