/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekaik-ne <ekaik-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:32:49 by ekaik-ne          #+#    #+#             */
/*   Updated: 2023/03/21 15:30:44 by ekaik-ne         ###   ########.fr       */
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
    int     echo;
    int     flag;
    char    *print;
    int     fd;
    
}   t_echo;

typedef struct s_cd
{
    int     cd;
    char    *path;
}   t_cd;

typedef struct s_export
{
    int     export;
    char    *name;
    char    *value;

}   t_export;

typedef struct s_env
{
    int     env;
    char    *print;
    int     fd;

}   t_env;

typedef struct s_pdw
{
    int     pdw;
    char    *print;
    int     fd;

}   t_pwd;

typedef struct s_unset
{
    int     unset;
    char    *name;
    char    *value;

}   t_unset;

typedef struct s_exit
{
    int exit;

}   t_exit;

typedef struct s_var
{
	char				*name;
	char				*content;
	struct s_var		*next;

}	t_var;

typedef struct s_error
{
    int     error;
    char    *print;

}   t_error;


typedef struct s_data
{
    t_echo          echo;
    t_cd            cd;
    t_export        export;
    t_env           env;
    t_pwd           pwd;
    t_unset         unset;
    t_exit          exit;
    t_var           *var;
    t_error         error;
    pid_t           pid;
    int             fd;
    char            **envp;
    int teste;
    char            path_comand[PATH_MAX];
    
}   t_data;

extern t_data	g_data;

t_var   *ft_new_lst_var(char *title, char *value);
void    ft_add_lst_var(t_var **var, t_var *new);
t_var   *ft_lst_var_last(t_var *var);
void    ft_clear_var(t_var **var, void (*del)(char*));
void    ft_del_one_var(t_var *var, void (*del)(char*));
void    ft_del_var(char *content);

void ft_starting_variables(char **envp);
void ft_set_envp_t_var(char **envp);
void ft_get_folder(void);

void ft_check_line(char *line);
char **ft_broke_line(char *line);

int ft_its_a_redirector(char *line);
int ft_its_a_builtins(char *line);
void ft_builtins(char **line, int *index);
void ft_redirector(char **line, int *index);

void ft_print_error(char **line, int *index);

void ft_appending(char **line, int *index);
void ft_overwriting(char **line, int *index);
void ft_here_doc(char **line, int *index);
void ft_input(char **line, int *index);

void ft_cd(char **line, int *index);
char *ft_get_path_cd(char **line, int *index);

void ft_env(char **line, int *index);
void ft_get_print_env(void);
void ft_clear_env(void);

void ft_pwd(char **line, int *index);
void ft_clear_pwd(void); 

void ft_echo(char **line, int *index);
void ft_get_str_echo(char **line, int *index);
void ft_clear_echo(void);

void ft_clear_struct(void);

void ft_exit(char **line);

void ft_export(char **line, int *index);
void ft_adding_export(char **line, int *index);
int ft_check_name_var(char *str);

void ft_unset(char **line, int *index);
int ft_check_exist_var(char *name_var);
void ft_delete_var(char *name_var);

int ft_execute_ft_system(char **line, int *index);
char **ft_limit_execve(char **line, int *index);

void ft_clear_split_line(char **broke_line);

void ft_start_signals(void);
void ft_sig_new_prompt(int sig);
void ft_sig_close(int sig);


int ft_open_quotes(char *line);
char *ft_get_more_content(char *line);
int ft_count_split(char *str);


#endif