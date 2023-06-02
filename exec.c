/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:47:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 17:15:38 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_ft_system(char **line, int *index)
{
	char	**aux;
	char	*path;
	int		ret;

	aux = ft_limit_execve(line, index);
	if (aux == NULL)
		return (-1);
	path = ft_get_path_exec(aux[0]);

	if (path == NULL)
	{
		ft_clear_split_line(aux);
		if (aux != NULL)
			free(aux);
		return (-1);
	}
	ret = ft_execute_execve(aux, line, path, index);
	free(path);
	ft_clear_split_line(aux);
	if (aux != NULL)
		free(aux);
	return (ret);
}

char	*ft_get_path_exec(char *comand)
{
	t_var	*aux;
	char	**path_s;
	char	*path;
	char	*temp;

	aux = g_data.var;
	path_s = NULL;
	while (aux != NULL)
	{
		if (ft_strncmp(aux->name, "PATH", ft_strlen(aux->name)) == 0)
			break ;
		aux = aux->next;
	}
	if (aux != NULL)
	{
		temp = ft_strdup(aux->content);
		path_s = ft_split(temp, ':');
	}
	while (*path_s != NULL)
	{
		path = ft_strjoin(*path_s++, "/");
		path = ft_strjoin_mod(path, comand);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	if (*path_s == NULL)
		path = NULL;
	ft_clear_split_line(path_s);
	free(temp);
	return (path);
}

int	ft_execute_execve(char **aux, char **line, char *path, int *index)
{
	int		status;
	int		ret;
	pid_t	pid;

	ret = 0;
	status = 0;
	pid = -1;
	ft_redirector_in_exec(line, index);
	if (g_data.jump_fork == 0)
		pid = fork();
	if (pid == 0 || g_data.jump_fork == 1)
		ret = execve(path, aux, g_data.envp);
	else if (pid > 0)
		waitpid(pid, &status, WUNTRACED);
	if (status > 0)
			ret = -1;
	return (ret);
}

void	ft_redirector_in_exec(char **line, int *index)
{
	while (line[*index] != NULL)
	{
		if (ft_its_a_redirector(line[*index], ft_strlen(line[*index])) > 0)
		{
			ft_redirector(line, index);
			if (ft_strlen(line[*index]) == 1 && line[*index][0] == '|')
				break ;
			if (g_data.fd == -1)
			{
				*index -= 1;
				ft_print_error(line, index);
			}
		}
		else
			break ;
	}
}

char	**ft_limit_execve(char **line, int *index)
{
	int		x;
	int		y;
	char	**aux;

	x = 0;
	y = 0;
	while (line[*index + x] != NULL && ft_its_a_redirector(line[*index + x],
			ft_strlen(line[*index + x])) == 0)
		x++;
	aux = (char **)malloc(sizeof(char *) * (x + 1));
	if (aux == NULL)
		return (NULL);
	while (y < x)
	{
		aux[y] = ft_strdup(line[*index + y]);
		y++;
	}
	aux[x] = NULL;
	*index += x;
	return (aux);
}
