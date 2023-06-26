/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:54:56 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/06/09 14:57:06 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_value_exit_execve(int status)
{
	if (g_data.exit_status != NULL)
		free(g_data.exit_status);
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == SIGINT)
			g_data.exit_status = ft_strdup("130");
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_printf("Quit");
			g_data.exit_status = ft_strdup("131");
			ft_printf("\n");
		}
	}
	else if (WIFEXITED(status) != 0)
		g_data.exit_status = ft_itoa(WEXITSTATUS(status));
	else
		g_data.exit_status = ft_strdup("0");
}

void	ft_update_status_code(char **spt, int *i)
{
	t_var	*aux;
	t_var	*temp;

	aux = g_data.var;
	temp = aux;
	*i += 1;
	while (temp != NULL)
	{
		if (temp->name[0] == '?' && ft_strlen(temp->name) == 1)
		{
			if (temp->content != NULL)
				free(temp->content);
			temp->content = ft_strdup(spt[*i]);
			break ;
		}
		temp = temp->next;
	}
	g_data.var = aux;
}

char	*ft_init_here_doc(char *EOF_s)
{
	char	*aux;

	g_data.heredoc_buf = ft_strdup("");
	while (1)
	{
		rl_on_new_line();
		aux = readline("> ");
		if (aux == NULL)
		{
			ft_printf("-Minishell: warning: here-document has been delimited ");
			ft_printf("by end-of-file (wanted `%s')\n", EOF_s);
			break ;
		}
		if (ft_strlen(EOF_s) == ft_strlen(aux)
			&& ft_strnstr(EOF_s, aux, ft_strlen(EOF_s)) != NULL)
			break ;
		g_data.heredoc_buf = ft_strjoin_mod(g_data.heredoc_buf, aux);
		g_data.heredoc_buf = ft_strjoin_mod(g_data.heredoc_buf, "\n");
		free(aux);
	}
	free(aux);
	return (ft_strdup(g_data.heredoc_buf));
}

void	ft_close_default_fd(void)
{
	close(0);
	close(1);
	close(2);
	close(g_data.original_fd[0]);
	close(g_data.original_fd[1]);
}

void	ft_check_final_value(char *line)
{
	if ((ft_strlen(line) >= 1 && (line[ft_strlen(line) - 1] == '>'
				|| line[ft_strlen(line) - 1] == '<')) || (ft_strlen(line) >= 2
			&& (line[ft_strlen(line) - 1] == '>' && line[ft_strlen(line) - 2]
				== '>')) || line[0] == '|')
	{
		printf("-Minishell: syntax error near unexpected token 'newline'\n");
		free(line);
		close(g_data.pipe[0]);
		ft_putstr_fd("?;", g_data.pipe[1]);
		ft_putstr_fd("2", g_data.pipe[1]);
		ft_clear_struct();
		ft_close_default_fd();
		exit(1);
	}
}
