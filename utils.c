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

void	ft_clear_struct(void)
{
	g_data.fd = 0;
	g_data.jump_fork = 0;
	if (g_data.env.env > 0)
		ft_clear_env();
	if (g_data.pwd.pdw > 0)
		ft_clear_pwd();
	if (g_data.echo.echo > 0)
		ft_clear_echo();
	ft_clear_var(&g_data.var);
	rl_clear_history();
	ft_clear_split_line(g_data.broke_line);
	if (g_data.broke_line != NULL)
		free(g_data.broke_line);
	if (g_data.line != NULL)
		free(g_data.line);
	close(g_data.pipe[0]);
	close(g_data.pipe[1]);
}

void	ft_starting_variables(char **envp)
{
	g_data.envp = envp;
	g_data.jump_fork = 0;
	ft_add_lst_var(&g_data.var, ft_new_lst_var(ft_strdup("?"), ft_strdup("0")));
	ft_set_envp_t_var(envp);
}

void	ft_set_envp_t_var(char **envp)
{
	int		index;
	char	**aux;

	index = 0;
	while (envp[index] != NULL)
	{
		aux = ft_split(envp[index++], '=');
		if (aux == NULL)
			break ;
		if (g_data.var == NULL)
			g_data.var = ft_new_lst_var(ft_strdup(aux[0]), ft_strdup(aux[1]));
		else
			ft_add_lst_var(&g_data.var, ft_new_lst_var(ft_strdup(aux[0]),
					ft_strdup(aux[1])));
		ft_clear_split_line(aux);
		if (aux != NULL)
			free(aux);
	}
}

char	*ft_get_folder(void)
{
	char	str[PATH_MAX];
	char	**folder;
	char	*temp;
	int		x;

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
			ft_clear_split_line(folder);
			if (folder != NULL)
				free(folder);
		}
	}
	temp = ft_strjoin_mod(temp, "$-> ");
	return (temp);
}

void	ft_check_line(char *line)
{
	int		index;
	char	**broke_line;

	index = 0;
	broke_line = NULL;
	g_data.line = line;
	getcwd(g_data.path_comand, sizeof(g_data.path_comand));
	broke_line = ft_broke_line(line);
	g_data.broke_line = broke_line;
	while (broke_line[index] != NULL)
	{
		if (ft_its_a_redirector(broke_line[index],
				ft_strlen(broke_line[index])) >= 1)
			ft_redirector(broke_line, &index);
		else if (ft_its_a_builtins(broke_line[index]) == 1)
			ft_builtins(broke_line, &index);
		else if (ft_execute_ft_system(broke_line, &index) != -1)
			continue ;
		else
			ft_print_error(broke_line, &index);
	}
}
