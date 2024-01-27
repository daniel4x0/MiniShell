/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:39:41 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 09:39:43 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

void	execute_builtins(t_commands *commands, t_mini *mini, t_list *cmd, int len)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(mini) && mini->toks)
		execve(mini->env, mini->toks, commands->envp);
	else if (mini->toks && !ft_strncmp(*mini->toks, "pwd", len) && len == 3)
		g_status = ft_pwd();
	else if (is_builtin(mini) && mini->toks && !ft_strncmp(*mini->toks, "echo", len) && len == 4)
		g_status = ft_echo(cmd);
	else if (is_builtin(mini) && mini->toks && !ft_strncmp(*mini->toks, "env", len) && len == 3)
	{
		fd_putmatrix(commands->envp, 1, 1);
		g_status = 0;
	}
}

void	*handle_redirection(t_list *cmd, int fd[2])
{
	t_mini	*mini;

	mini = cmd->content;
	if (mini->fdin != STDIN_FILENO)
	{
		if (dup2(mini->fdin, STDIN_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(mini->fdin);
	}
	if (mini->fdout != STDOUT_FILENO)
	{
		if (dup2(mini->fdout, STDOUT_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		close(mini->fdout);
	}
	else if (cmd->next && dup2(fd[1], STDOUT_FILENO) == -1)
		return (mini_perror(DUPERR, NULL, 1));
	close(fd[1]);
	return ("");
}

void	*mini_series(t_commands *commands, t_list *cmd, int fd[2])
{
	t_mini	*mini;
	int		len;

	mini = cmd->content;
	len = 0;
	if (mini->toks)
		len = ft_strlen(*mini->toks);
	handle_redirection(cmd, fd);
	close(fd[0]);
	execute_builtins(commands, mini, cmd, len);
	ft_lstclear(&commands->cmds, free_content);
	exit(g_status);
}