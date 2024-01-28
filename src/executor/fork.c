/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:39:52 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 09:39:54 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	execute_fork(t_commands *commands, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		mini_series(commands, cmd, fd);
}

void	*check_to_fork(t_commands *commands, t_list *cmd, int fd[2])
{
	t_mini	*mini;
	DIR		*directory;

	mini = cmd->content;
	directory = NULL;
	if (mini->toks)
		directory = opendir(*mini->toks);
	if (mini->fdin == -1 || mini->fdout == -1)
		return (NULL);
	if ((mini->env && access(mini->env, X_OK) == 0) || is_builtin(mini))
		execute_fork(commands, cmd, fd);
	else if (!is_builtin(mini) && \
		((mini->env && !access(mini->env, F_OK)) || directory))
		g_status = 126;
	else if (!is_builtin(mini) && mini->toks)
		g_status = 127;
	if (directory)
		closedir(directory);
	return ("");
}
