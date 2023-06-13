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

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

typedef struct s_echo
{
	int		echo;
	int		flag;
	char	*print;
	int		fd;
}	t_echo;

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

typedef struct s_data
{
	t_echo		echo;
	t_env		env;
	t_pwd		pwd;
	t_var		*var;
	t_error		error;
	pid_t		pid;
	int			pipe[2];
	int			fd;
	int			non_blocking;
	char		**envp;
	int			jump_fork;
	char		*line;
	char		**broke_line;
	char		path_comand[PATH_MAX];
	char		*exit_status;
	int			original_fd[2];
}	t_data;

extern t_data	g_data;

t_var		*ft_new_lst_var(char *title, char *value);
void		ft_add_lst_var(t_var **var, t_var *new);
t_var		*ft_lst_var_last(t_var *var);
void		ft_clear_var(t_var **var);
void		ft_del_one_var(t_var *var);
void		ft_starting_variables(char **envp);
void		ft_set_envp_t_var(char **envp);
char		*ft_get_folder(void);
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
void		ft_get_str_echo(char **line, int *i);
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
int			ft_len_quotes(char *str, char quote, int i);
int			ft_link_var(char *dest, char *var, int i);
int			ft_break_redirector(char *str, int pos);
int			ft_split_redirection(char *str);
int			ft_len_redirector(char *str, int index, int len_backup);
int			ft_execute_execve(char **aux, char **line, char *path, int *index);
void		ft_redirector_in_exec(char **line, int *index);
char		*ft_add_history(void);
void		ft_pipe(char **line, int *index);
void		ft_check_next_comand(char **line, int *index);
void		ft_init(char *line);
char		*ft_get_path_exec(char *comand);
void		ft_update_parent(char *aux);
void		ft_start_signals_parent(void);
void		ft_new_prompt(int sig);
void		ft_start_signal_child(void);
void		ft_kill_child(int sig);
void		ft_start_signal_execve(pid_t pid);
void		ft_kill_execve(int sig);
char		*ft_validate_path(char **path_s, char *comand, char *temp);
void		ft_exit_parent(char **split, char *line);
void		ft_parent_init(char *line);
char		*ft_verify_line(void);
char		ft_get_quote_open(char *line);
void		ft_get_value_exit_execve(int status);
void		ft_update_status_code(char **spt, int *i);
char		*ft_init_here_doc(char *EOF_s);
void		ft_close_default_fd(void);
void		ft_check_final_value(char *line);
void		ft_adding_or_replacing_export(char *name, char *vl);

#endif
