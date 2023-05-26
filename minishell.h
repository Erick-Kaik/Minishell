/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:32:49 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/05/22 13:39:04 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_echo
{
	int		echo;
	int		flag;
	char	*print;
	int		fd;
}	t_echo;

typedef struct s_cd
{
	int		cd;
	char	*path;
}	t_cd;

typedef struct s_export
{
	int		export;
	char	*name;
	char	*value;
}	t_export;

typedef struct s_env
{
	int		env;
	char	*print;
	int		fd;
}	t_env;

typedef struct s_pdw
{
	int		pdw;
	char	*print;
	int		fd;
}	t_pwd;

typedef struct s_unset
{
	int		unset;
	char	*name;
	char	*value;
}	t_unset;

typedef struct s_exit
{
	int	exit;
}	t_exit;

typedef struct s_var
{
	char			*name;
	char			*content;
	struct s_var	*next;
}	t_var;

typedef struct s_error
{
	int		error;
	char	*print;
}	t_error;

typedef struct s_history
{
	char				*str;
	struct s_history	*next;
}	t_history;

typedef struct s_data
{
	t_echo		echo;
	t_cd		cd;
	t_export	export;
	t_env		env;
	t_pwd		pwd;
	t_unset		unset;
	t_exit		exit;
	t_var		*var;
	t_error		error;
	t_history	*history;
	pid_t		pid;
	int			fd;
	char		**envp;
	int			status;
	char		path_comand[PATH_MAX];
}	t_data;

extern t_data	g_data;

t_var		*ft_new_lst_var(char *title, char *value);
void		ft_add_lst_var(t_var **var, t_var *new);
t_var		*ft_lst_var_last(t_var *var);
void		ft_clear_var(t_var **var, void (*del)(char*));
void		ft_del_one_var(t_var *var, void (*del)(char*));
void		ft_del_var(char *content);
void		ft_starting_variables(char **envp);
void		ft_set_envp_t_var(char **envp);
void		ft_get_folder(void);
void		ft_check_line(char *line);
char		**ft_broke_line(char *line);
int			ft_its_a_redirector(char *line, int len);
int			ft_its_a_builtins(char *line);
void		ft_builtins(char **line, int *index);
void		ft_redirector(char **line, int *index);
void		ft_print_error(char **line, int *index);
void		ft_appending(char **line, int *index);
void		ft_overwriting(char **line, int *index);
void		ft_here_doc(char **line, int *index);
void		ft_input(char **line, int *index);
void		ft_cd(char **line, int *index);
char		*ft_get_path_cd(char **line, int *index);
void		ft_env(char **line, int *index);
void		ft_get_print_env(void);
void		ft_clear_env(void);
void		ft_pwd(char **line, int *index);
void		ft_clear_pwd(void);
void		ft_echo(char **line, int *index);
void		ft_get_str_echo(char **line, int *index);
void		ft_clear_echo(void);
void		ft_clear_struct(void);
void		ft_exit(char **line);
void		ft_export(char **line, int *index);
void		ft_adding_export(char **line, int *index);
int			ft_check_name_var(char *str);
void		ft_unset(char **line, int *index);
int			ft_check_exist_var(char *name_var);
void		ft_delete_var(char *name_var);
int			ft_execute_ft_system(char **line, int *index);
char		**ft_limit_execve(char **line, int *index);
void		ft_clear_split_line(char **broke_line);
void		ft_start_signals(void);
void		ft_sig_new_prompt(int sig);
void		ft_sig_close(int sig);
int			ft_open_quotes(char *line);
char		*ft_get_more_content(char *line, int *concat);
int			ft_count_split(char *str);
int			ft_jump_quotes(char *str, char quote, int i);
char		**ft_split_words(char *str, char **split, int count);
int			ft_lenth_split(char *str, int *i);
char		*ft_check_var(char *str, int i, int *index);
char		*ft_get_var(char *name_var);
void		ft_fill_split(char *dest, char *str, int start, int len);
int			ft_fix_index_position(char *str, int i);
void		ft_clear_pid(pid_t pid);
int			ft_len_quotes(char *str, char quote, int i);
int			ft_link_var_in_split(char *dest, char* var, int i);
int			ft_break_redirector(char *str, int pos);
int			ft_split_redirection(char *str);
int			ft_len_redirector(char *str, int index, int len_backup);
int			ft_execute_execve(char **aux, char **line, char *path, int *index);
void		ft_redirector_in_exec(char** line, int *index);
t_history	*ft_new_lst_history(char *content);
void		ft_add_lst_history(t_history **history, t_history *new);
t_history	*ft_lst_history_last(t_history *history);
void		ft_clear_history(t_history **history, void (*del)(char*));
void		ft_del_one_history(t_history *history, void (*del)(char*));
void		ft_del_history(char *content);
void		ft_add_history(char *aux);


#endif
