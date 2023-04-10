/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:51:04 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/09 10:13:58 by ekaik-ne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_var
{
	char				*name;
	char				*content;
	struct s_var		*next;
}	t_var;

typedef struct s_history
{
	char				*num;
	char				*comand;
	struct s_history	*next;
}	t_history;

t_var	*ft_new_lst_var(char *title, char *value);
void	ft_add_lst_var(t_var **lst, t_var *new);
t_var	*ft_lst_var_last(t_var *var);
void	ft_add_value_last_com(t_var **var, char *value);
void ft_print_env_other_var(int fd, t_var *var);

char *ft_jump_spaces(char const *str, char *comand);
void ft_read_comand(char *str, t_var **var, t_history **history);
void ft_echo(char *txt, t_var **var);
char *ft_check_echo(char *txt, int *fd, t_var **var);
void ft_cd(char *str, t_var **var);
void ft_pwd(char *str, t_var **var);
void ft_env(char *str, t_var **var);
char *ft_get_var(char *str);
char *ft_get_folder(void);
void ft_exit();
int ft_check_two_quotes(char *str, t_var **var);
int ft_single_quote(int pos, char *str, int fd);
int ft_double_quote(int pos, char *str, int fd, t_var **var);
int ft_check_variable(int pos, char *str, int fd, t_var **var);
int ft_check_redirector(char *str);
char *ft_get_file(char *str);
int ft_rd_output(char *str);
int ft_rd_last_output(char *str);
int ft_rd_input(char *str);
int ft_rd_loop_input(char *str);
char *ft_str_echo(char *str);
void ft_vl_last_comand(t_var **var, int solo);
int ft_echo_last_comand(t_var **var, int fd);
void ft_export(char *varaible, t_var **var);
void ft_apply_title_value(char *varaible, char **title, char **value, t_var **var);
int ft_check_f_var(char *str);
void ft_format_value(char **str, t_var **var);
int ft_count_temp_to_str(char *temp,  t_var **var);
int ft_format_quotes(char *str, char quote);
char *ft_fill_value_var(char *temp, int size);
void ft_print_error(char *str, t_var **var);
int ft_check_f_var(char *str);
void ft_unset(char *varaible, t_var **var);
char *ft_print_var(t_var *var, char *amb);
t_history	*ft_new_lst_history(char *num, char *comand);
void	ft_add_lst_history(t_history **history, t_history *new);
t_history *ft_lst_history_last(t_history *history);
int ft_get_size_history(t_history *history);
void ft_add_history(char *str, t_history **history);
void ft_history(char *str, t_history *history, t_var **var);
char *ft_save_str_history(char *str);
t_var *ft_create_and_send_var(int create, char **env);
void ft_sig_new_prompt(int sig);
t_history *ft_create_and_send_history(int create);
void ft_sig_close(int sig);
char *ft_filter_str_amb(char *amb);
char *ft_rest_of_str_amb(char *filter, char *amb);
void	ft_clear_history(t_history **history, void (*del)(char*));
void	ft_del_one_history(t_history *history, void (*del)(char*));
void	ft_del_history(char *content);
void	ft_clear_var(t_var **var, void (*del)(char*));
void	ft_del_one_var(t_var *var, void (*del)(char*));
void	ft_del_var(char *content);

void ft_signals(void);

#endif