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

# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# define READ 0
# define WRITE 1

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

char	*mini_readline(t_commands *commands, char *str);
void	*mini_here_fd(int fd[2]);
int		builtin(t_commands *commands, t_list *cmd, int *is_exit, int n);
int		is_builtin(t_mini *n);
int		ft_cd(t_commands *commands);
int		ft_pwd(void);
int		ft_echo(t_list *cmd);
int		ft_export(t_commands *commands);
int		ft_unset(t_commands *commands);
int		ft_exit(t_list *cmd, int *is_exit);
void	*run_lexer(char *out, t_commands *p);
char	**tokenize_commands(char const *s, char *set);
char	**tokenize_mutable_commands(char const *s, char *set);
char	*full_trim(char const *str, int in_quotes_single, int in_quotes_double);
t_list	*node_refil(char **args, int i);
int	get_fd(char *full_path, int oldfd, int read_or_write, int write);
t_mini	*fd_out_a(t_mini *node, char **args, int *i);
t_mini	*fd_out_b(t_mini *node, char **args, int *i);
t_mini	*fd_in_a(t_mini *node, char **args, int *i);
t_mini	*fd_in_b(t_mini *node, char **args, int *i);
void	*execute_commands(t_commands *commands, t_list *cmd);
void	*check_to_fork(t_commands *commands, t_list *cmd, int fd[2]);
void	execute_builtins(t_commands *commands, t_mini *mini, t_list *cmd, int len);
void	execute_hm(char ***out, char *full, char *args, char **envp);
int		exec_builtin(t_commands *commands, int (*func)(t_commands *));
void	cmd_extract(t_commands *commands, t_list *start, \
		char **split_path, char *path);
char	*env_expander(t_commands *commands, char *str, int index);
char	*handle_env_tilde(char *str, char *tilde, int index);
char	*get_here_str(char *newstr, char *str, size_t len, char *max, char *err);
int		here_docs(char *newstr, char *str, char *delimeter, char *err);
void	*mini_perror(int err_type, char *param, int err);
char	*get_env_char(char	*var, char **envp, int n);
char	**set_env_char(char *var, char *value, char **envp, int n);
char	*mini_getcommands(t_commands commands);
void	free_content(void *content);
void	handle_sigint(int sig);
void	handle_sigint_child(int sig);
void	free_matrix(char ***m);
char	**dup_matrix(char **m);
int		open_quotes_flag(const char *command, char *delimeter);
int		open_mutable_quotes_flag(char *str, char *delimiter);
char	**handle_quotes(char **result, const char *str, char *delimeter);
char	**handle_mutable_quotes(char **result, char *str, char *delimeter);
char	**tokenize_commands(char const *str, char *delimeter);
char	**tokenize_mutable_commands(char const *str, char *delimeter);
int		len_matrix(char **m);
char	**swap_matrix(char ***big, char **small, int n);
char	**extend_matrix(char **in, char *newstr);
int		fd_putmatrix(char **m, int nl, int fd);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
char	*toks_extract(t_commands *commands, char *str, int i);
void	*parse_input(char **args, t_commands *p);
char	**switch_matrix(t_commands *commands, char **args);
DIR		*check_cmd(t_commands *commands, t_list *cmd, char ***s, char *path);
t_commands	initialize_env(t_commands commands, char *str, char **argv);
t_commands	initialize_commands(char **argv, char **envp);
void	mini_getpid(t_commands *p);
t_mini	*initialize_mini(void);
void	cd_error(char **mx1, char **mx2);
int		check_equalsign(char *argv, char **envp, int index);
int		amount_of_space(char const *str);
void	read_line_and_update(char ***m, int fd);
char	*find_cmd(char **env_path, char *cmd, char *full_path);
t_mini	*handle_pipe_redir(t_mini *mini, char **store1, char **store2, int *i);
char	**trim_dump(char **args);
t_list	*end_fill(t_list *cmds, char **args, char **temp);
void	*handle_redirection(t_list *cmd, int fd[2]);
void	*mini_series(t_commands *commands, t_list *cmd, int fd[2]);
#endif
