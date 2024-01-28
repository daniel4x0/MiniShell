/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:38:07 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/28 15:38:09 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void	execute_hm(char ***out, char *full, char *args, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**m;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		m = ft_split(args, ' ');
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!access(full, F_OK))
			execve(full, m, envp);
		exit (1);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	read_line_and_update(out, fd[0]);
	close(fd[0]);
}

int	get_fd(char *full_path, int oldfd, int read_or_write, int write)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!full_path)
		return (-1);
	if (access(full_path, F_OK) == -1 && !read_or_write)
		mini_perror(NDIR, full_path, 127);
	else if (!read_or_write && access(full_path, R_OK) == -1)
		mini_perror(NPERM, full_path, 126);
	else if (read_or_write && access(full_path, W_OK) \
			== -1 && access(full_path, F_OK) == 0)
		mini_perror(NPERM, full_path, 126);
	if (read_or_write && write)
		fd = open(full_path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (read_or_write && !write)
		fd = open(full_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (!read_or_write && oldfd != -1)
		fd = open(full_path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_list	*node_refil(char **args, int i)
{
	t_list	*cmds[2];
	char	**store1;
	char	**store2;

	cmds[0] = NULL;
	store2 = trim_dump(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(initialize_mini()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		store1 = args;
		cmds[1]->content = handle_pipe_redir \
		(cmds[1]->content, store1, store2, &i);
		if (i < 0)
			return (end_fill(cmds[0], args, store2));
		if (!args[i])
			break ;
	}
	free_matrix(&store2);
	free_matrix(&args);
	return (cmds[0]);
}
