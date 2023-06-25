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

	if (ft_strlen(line[*index]) <= 0)
		return (-1);
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
	g_data.args_exec = aux;
	g_data.path_exec = path;
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
	path = NULL;
	temp = NULL;
	if (comand[0] == '/')
	{
		if (access(comand, X_OK) == 0 && access(comand, F_OK) == 0)
			return (ft_strdup(comand));
		return (NULL);
	}
	while (aux != NULL && temp == NULL)
	{
		if (ft_strncmp(aux->name, "PATH", ft_strlen(aux->name)) == 0)
			temp = ft_strdup(aux->content);
		aux = aux->next;
	}
	if (temp == NULL)
		return (NULL);
	path = ft_validate_path(path_s, comand, temp);
	return (path);
}

char	*ft_validate_path(char **path_s, char *comand, char *temp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	path_s = ft_split(temp, ':');
	while (path_s[i] != NULL)
	{
		path = ft_strjoin(path_s[i++], "/");
		path = ft_strjoin_mod(path, comand);
		if (access(path, X_OK) == 0 && access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	ft_clear_split_line(path_s);
	if (path_s != NULL)
		free(path_s);
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
	ft_start_signal_execve(pid);
	if (pid == 0 || g_data.jump_fork == 1)
	{
		ret = execve(path, aux, g_data.envp);
		ft_clear_split_line(aux);
		free(aux);
		free(path);
		ft_print_error(line, index);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, WUNTRACED);
	ft_get_value_exit_execve(status);
	return (ret);
}

char	**ft_limit_execve(char **line, int *index)
{
	int		x;
	int		y;
	char	**aux;

	x = 0;
	y = -1;
	while (line[*index + x] != NULL && ft_its_a_redirector(line[*index + x],
			ft_strlen(line[*index + x])) == 0)
		x++;
	aux = (char **)malloc(sizeof(char *) * (x + 1));
	if (aux == NULL)
		return (NULL);
	while (++y < x)
	{
		if (ft_strlen(line[*index + y]) > 1 && line[*index + y][0] == '~'
			&& line[*index + y][1] == '/')
			aux[y] = ft_strjoin(getenv("HOME"), &line[*index + y][1]);
		else if (ft_strlen(line[*index + y]) == 1 && line[*index + y][0] == '~')
			aux[y] = ft_strdup(getenv("HOME"));
		else
			aux[y] = ft_strdup(line[*index + y]);
	}
	aux[x] = NULL;
	*index += x;
	return (aux);
}
