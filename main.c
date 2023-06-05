/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:30:08 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 15:58:38 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (argc > 1 || argv == NULL)
		return (0);
	ft_starting_variables(envp);
	ft_start_signals_parent();
	line = "";
	ft_add_lst_history(&g_data.history, ft_new_lst_history(line));
	ft_init(line);
	return (0);
}

void	ft_init(char *line)
{
	char	*aux;

	while (1)
	{
		if (g_data.pid != -1)
			line = ft_add_history();
		pipe(g_data.pipe);
		g_data.pid = fork();
		if (g_data.pid < 0)
			continue ;
		else if (g_data.pid == 0)
		{
			ft_start_signal_child();
			if (line != NULL)
				ft_check_line(line);
			exit(1);
		}
		else if (g_data.pid > 0)
		{

			waitpid(g_data.pid, NULL, WUNTRACED);
			aux = ft_calloc((ft_strlen(line) + 2), sizeof(char));
			close(g_data.pipe[1]);
			if (read(g_data.pipe[0], aux, ft_strlen(line) + 1) > 0)
				ft_update_parent(aux);
			close(g_data.pipe[0]);
			free(aux);
		}
		free(line);
	}
}

void	ft_update_parent(char *aux)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(aux, ':');
	if (ft_strlen(split[0]) == 6 && ft_strnstr(split[0], "export", 6) != NULL)
		ft_export(split, &i);
	else if (ft_strlen(split[0]) == 5 && ft_strnstr(split[0], "unset", 5) != NULL)
		ft_unset(split, &i);
	else if (ft_strlen(split[0]) == 4 && ft_strnstr(split[0], "exit", 5) != NULL)
		ft_exit_parent(split, aux);
	else if (ft_strlen(split[0]) == 2 && ft_strnstr(split[0], "cd", 2) != NULL)
		ft_cd(split, &i);
	ft_clear_split_line(split);
}

char	*ft_add_history(void)
{
	int		concat;
	char	*line;
	char	*aux;
	t_history *com;

	concat = 0;
	ft_get_folder();
	line = readline(" ");
	if (line == NULL)
	{
		rl_replace_line("", 0);
		ft_clear_var(&g_data.var, &ft_del_var);
		rl_clear_history();
		exit(1);
	}
	aux = ft_strtrim(line, " ");
	if (ft_strlen(aux) <= 0)
	{
		free(aux);
		rl_on_new_line();
		rl_redisplay();
		return (NULL);
	}
	while (ft_open_quotes(aux) == 1 || aux[ft_strlen(aux) - 1] == '|')
		aux = ft_get_more_content(aux, &concat);
	com = ft_new_lst_history(ft_strdup(aux));
	ft_add_lst_history(&g_data.history, com);
	add_history(com->str);
	free(aux);
	free(line);
	return (com->str);
}
