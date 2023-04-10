/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 21:22:32 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/08 13:14:38 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(char *str, t_var **var)
{
	char path[PATH_MAX];
	char *temp;
	int fd;

	ft_add_value_last_com(var, "0");
    fd = 0;
	temp = ft_jump_spaces(ft_strtrim(str, "\n"), "pwd");
	if (temp != NULL)
		fd = ft_check_redirector(temp);
	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, fd);
		ft_putchar_fd('\n', fd);
	}
}
