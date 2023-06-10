/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:58:33 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 17:11:20 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirector(char **line, int *index)
{
	if (ft_strlen(line[*index]) == 2)
	{
		if (line[*index][0] == '>' && line[*index][1] == '>')
			ft_appending(line, index);
		else if (line[*index][0] == '<' && line[*index][1] == '<')
			ft_here_doc(line, index);
	}
	else if (ft_strlen(line[*index]) == 1)
	{
		if (line[*index][0] == '>')
			ft_overwriting(line, index);
		else if (line[*index][0] == '<')
			ft_input(line, index);
		else if (line[*index][0] == '|')
			ft_pipe(line, index);
	}
}

void	ft_appending(char **line, int *index)
{
	char	*aux_path;

	aux_path = NULL;
	getcwd(aux_path, sizeof(aux_path));
	if (aux_path != NULL)
		chdir(g_data.path_comand);
	if (ft_strlen(line[*index]) == 2
		&& line[*index][0] == '>' && line[*index][1] == '>')
		*index += 1;
	else
		return ;
	g_data.fd = open(line[*index], O_WRONLY
			| O_CREAT | O_APPEND | O_SYNC, 0777);
	dup2(g_data.fd, STDOUT_FILENO);
	if (aux_path != NULL)
		chdir(aux_path);
	*index += 1;
}

void	ft_overwriting(char **line, int *index)
{
	char	*aux_path;

	aux_path = NULL;
	getcwd(aux_path, sizeof(aux_path));
	if (aux_path != NULL)
		chdir(g_data.path_comand);
	if (ft_strlen(line[*index]) == 1 && line[*index][0] == '>')
		*index += 1;
	else
		return ;
	g_data.fd = open(line[*index], O_WRONLY
			| O_CREAT | O_TRUNC | O_SYNC, 0777);
	dup2(g_data.fd, STDOUT_FILENO);
	if (aux_path != NULL)
		chdir(aux_path);
	*index += 1;
}

void	ft_here_doc(char **line, int *index)
{
	char	*buffer;
	char	*aux;

	buffer = "";
	if (ft_strlen(line[*index]) == 2 && line[*index][0] == '<'
		&& line[*index][1] == '<')
		*index += 1;
	while (1)
	{
		rl_on_new_line();
		aux = readline("> ");
		if (buffer != NULL)
			buffer = ft_strjoin(buffer, aux);
		if (aux == NULL)
		{
			ft_printf("-Minishell: warning: here-document has been delimited ");
			ft_printf("by end-of-file (wanted `%s')\n", line[*index]);
			break ;
		}
		if (ft_strlen(line[*index]) == ft_strlen(aux)
			&& ft_strnstr(line[*index], aux, ft_strlen(line[*index])) == NULL)
			buffer = ft_strjoin(buffer, "\n");
		else
			break ;
		free(aux);
	}
	g_data.fd = open("/tmp/tempfile", O_RDWR | O_TMPFILE | O_SYNC, 0777);
	write(tmpfd, buffer, ft_strlen(buffer));
	printf
	free(aux);
	*index += 1;
}

void	ft_input(char **line, int *index)
{
	char	*aux_path;

	aux_path = NULL;
	getcwd(aux_path, sizeof(aux_path));
	if (aux_path != NULL)
		chdir(g_data.path_comand);
	if (ft_strlen(line[*index]) == 1 && line[*index][0] == '<')
		*index += 1;
	while (line[*index] != NULL)
	{
		g_data.fd = open(line[*index], O_RDONLY, 0777);
		if (g_data.fd < 0 || line[*index + 1] == NULL
			|| ft_its_a_redirector(line[*index + 1],
				ft_strlen(line[*index + 1])) > 0)
		{
			*index += 1;
			break ;
		}
		*index += 1;
	}
	if (g_data.fd >= 0)
		dup2(g_data.fd, 0);
	if (aux_path != NULL)
		chdir(aux_path);
}