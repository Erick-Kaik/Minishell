/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:12:25 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/16 17:47:23 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//vem o unset e dps tem q pegar todos os indices da frente e apagar, msm q algum no meio n apague o resto sim

void ft_unset(char **line, int *index)
{
    *index += 1;
    while (line[*index] != NULL && ft_its_a_redirector(line[*index]) == 0)
    {
        
    }
    
}