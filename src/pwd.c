/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:06:39 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/16 20:42:55 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **line, int *index)
{
	char	path[PATH_MAX];
	int		ret;

	*index += 1;
	g_data.pwd.pdw = *index;
	while (line[*index] != NULL)
	{
		ret = ft_its_a_redirector(line[*index], ft_strlen(line[*index]));
		if (ret == 1)
		{
			ft_redirector(line, index);
			if (ft_strlen(line[*index]) == 1 && line[*index][0] == '|')
				*index += 1;
		}
		else
			*index += 1;
	}
	if (getcwd(path, sizeof(path)) != NULL)
		g_data.pwd.print = path;
	printf("%s\n", g_data.pwd.print);
	g_data.exit_status = ft_strdup("0");
}

void	ft_clear_pwd(void)
{
	if (g_data.pwd.pdw > 0)
		g_data.pwd.pdw = 0;
	if (g_data.pwd.fd != 0)
		g_data.pwd.fd = 0;
	if (g_data.pwd.print != NULL)
		g_data.pwd.print = NULL;
}