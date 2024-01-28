/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:47:55 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 10:47:58 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>

typedef struct s_commands
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_commands;

typedef struct s_mini
{
	char	**toks;
	char	*env;		//cambiato da matrice *da ricambiare
	int		fdin;
	int		fdout;
	int		args;
	int		toks_count;
	int		cmds_count;
}			t_mini;

//minishell.c
void		cmd_extract(t_commands *commands, \
			t_list *cmd, char **str, char *path);
char		*get_env_char(char *env, char **envp, int n);
void		get_pid(t_commands *commands);
void		*run_lexer(char *input, t_commands *commands);

//builtins.c
int			builtin(t_commands *commands, t_list *cmd, int *is_exit, int n);
int			is_builtin(t_mini *n);

//cd.c
void		cd_error(char **mx1, char **mx2);
int			ft_cd(t_commands *commands);

//echo.c
int			ft_echo(t_list *cmd, int flag);

//env.c
char		**set_env_char(char *var, char *value, char **envp, int n);

//error.c
void		*mini_perror(int err_type, char *param, int err);

//exit.c
int			ft_exit(t_list *cmd, int *is_exit, long i);

//export.c
int			check_equalsign(char *argv, char **envp, int index[2]);
int			ft_export(t_commands *commands);

//pwd.c
int			ft_pwd(void);

//unset.c
int			ft_unset(t_commands *commands);

//children.c
void		execute_builtins(t_commands *commands, \
			t_mini *mini, t_list *cmd, int len);
void		*handle_redirection(t_list *cmd, int fd[2]);
void		*mini_series(t_commands *commands, t_list *cmd, int fd[2]);

//exec_utils.c
void		execute_hm(char ***out, char *full, char *args, char **envp);
int			get_fd(char *full_path, int oldfd, int read_or_write, int write);
t_list		*node_refil(char **args, int i);

//executor.c
void		read_line_and_update(char ***m, int fd);
/*char		*here_string(char *newstr, char *str, \
			char *max, char *err);*/
			char	*here_string(char *str[2], size_t len, char *limit, char *warn);
void		*execute_commands(t_commands *commands, t_list *cmd);

//filedescriptors.c
t_mini		*fd_out_a(t_mini *mini, char **args, int *i);
t_mini		*fd_out_b(t_mini *mini, char **args, int *i);
t_mini		*fd_in_a(t_mini *mini, char **args, int *i);
t_mini		*fd_in_b(t_mini *mini, char **args, int *i);

//fork.c
void		execute_fork(t_commands *commands, t_list *cmd, int fd[2]);
void		*check_to_fork(t_commands *commands, t_list *cmd, int fd[2]);

//heredocument.c
//int			here_docs(char *newstr, char *str, char *delimeter, char *err);
int	here_docs(char *str[2], char *aux[2]);
//count.c
int			amount_of_space(char const *str);
int			open_mutable_quotes_flag(char *str, char *delimiter);
int			open_quotes_flag(const char *command, char *delimeter);

//parser.c
char		*full_trim(char const *str, \
			int in_quotes_single, int in_quotes_double);
char		*env_expander(t_commands *commands, char *str, int index);
void		*parse_input(char **args, t_commands *commands);

//tokenizer_utils.c
char		*handle_env_tilde(char *str, char *tilde, int index);
char		*toks_extract(t_commands *commands, char *str, int i);

//tokenizer.c
char		**handle_mutable_quotes(char **result, char *str, char *delimeter);
char		**handle_quotes(char **result, const char *str, char *delimeter);
char		**tokenize_mutable_commands(char const *str, char *delimeter);
char		**tokenize_commands(char const *str, char *delimeter);

//signal.c
void		handle_sigint(int sig);

//commandutils.c
char		*find_cmd(char **env_path, char *cmd, char *full_path);
DIR			*check_cmd(t_commands *commands, t_list *cmd, \
			char ***s, char *path);
t_mini		*handle_pipe_redir(t_mini *mini, char **store1, \
			char **store2, int *i);
char		**trim_dump(char **args);

//initialize.c
t_commands	initialize_env(t_commands commands, char *str, char **argv);
t_mini		*initialize_mini(void);
t_commands	initialize_commands(char **argv, char **envp);
void		free_content(void *content);
t_list		*end_fill(t_list *cmds, char **args, char **store);

//matrixops.c
int			len_matrix(char **m);
char		**swap_matrix(char ***args, char **swap, int index);
char		**switch_matrix(t_commands *commands, char **args);

//matrixops2.c
void		free_matrix(char ***m);
void		free_matrix_d(char **m);
char		**dup_matrix(char **m);
int			fd_putmatrix(char **m, int nl, int fd);
char		**extend_matrix(char **str, char *newstr);
#endif
