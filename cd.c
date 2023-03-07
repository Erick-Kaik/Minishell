/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 18:46:06 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/02/09 17:33:59 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(char *str, t_var **var)
{
	char	*path;
	char	*s_value;
	int		value;

	path = ft_jump_spaces(str, "cd");
	value = chdir(path);
	s_value = ft_itoa(value);
	ft_add_value_last_com(var, s_value);
	if (value != 0)
		ft_printf("No such file or director\n");
	free(path);
	free(s_value);
}
