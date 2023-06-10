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
	g_data.original_fd[0] = dup(STDIN_FILENO);
	g_data.original_fd[1] = dup(STDOUT_FILENO);
	ft_init(line);
	return (0);
}

void	ft_init(char *line)
{
	while (1)
	{
		if (g_data.pid != -1)
			line = ft_add_history();
		if (line == NULL)
			continue ;
		pipe(g_data.pipe);
		g_data.pid = fork();
		if (g_data.pid < 0)
			continue ;
		else if (g_data.pid == 0)
		{
			ft_start_signal_child();
			if (line != NULL)
				ft_check_line(line);
			ft_clear_struct();
			close(0);
			close(1);
			close(2);
			exit(1);
		}
		else if (g_data.pid > 0)
			ft_parent_init(line);
		free(line);
		g_data.pid = 0;
	}
}

void	ft_parent_init(char *line)
{
	char	*aux;

	aux = NULL;
	waitpid(g_data.pid, NULL, WUNTRACED);
	if (line == NULL && ft_strlen_mod(line, ' ') <= 0)
	{
		ft_clear_struct();
		rl_replace_line("", 0);
		rl_on_new_line();
		return ;
	}
	aux = ft_calloc((ft_strlen(line) + 10), sizeof(char));
	close(g_data.pipe[1]);
	if (read(g_data.pipe[0], aux, ft_strlen(line) + 10) > 0)
		ft_update_parent(aux);
	close(g_data.pipe[0]);
	free(aux);
}

void	ft_update_parent(char *aux)
{
	char	**spt;
	int		i;

	i = 0;
	spt = ft_split(aux, ':');
	while (spt[i] != NULL)
	{
		if (ft_strlen(spt[i]) == 6 && ft_strnstr(spt[i], "export", 6) != NULL)
			ft_export(spt, &i);
		else if (ft_strlen(spt[i]) == 5
			&& ft_strnstr(spt[i], "unset", 5) != NULL)
			ft_unset(spt, &i);
		else if (ft_strlen(spt[i]) == 2 && ft_strnstr(spt[i], "cd", 2) != NULL)
			ft_cd(spt, &i);
		else if (ft_strlen(spt[i]) == 1 && spt[i][0] == '?')
			ft_update_status_code(spt, &i);
		i++;
	}
	if (ft_strlen(spt[0]) == 4 && ft_strnstr(spt[0], "exit", 4) != NULL)
		ft_exit_parent(spt, aux);
	ft_clear_split_line(spt);
	if (spt != NULL)
		free(spt);
}

char	*ft_add_history(void)
{
	int			concat;
	char		*line;
	char		*aux;

	concat = 0;
	line = ft_verify_line();
	if (line == NULL)
		return (line);
	aux = ft_strtrim(line, " ");
	free(line);
	while (ft_open_quotes(aux) == 1 || aux[ft_strlen(aux) - 1] == '|')
	{
		aux = ft_get_more_content(aux, &concat);
		if (aux == NULL)
			return (NULL);
	}
	add_history(aux);
	return (aux);
}
