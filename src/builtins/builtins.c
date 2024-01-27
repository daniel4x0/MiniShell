/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:07:33 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/26 22:07:35 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

int	builtin(t_commands *commands, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_mini *)cmd->content)->toks;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_status = ft_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_status = ft_cd(commands);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_status = ft_export(commands);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_status = ft_unset(commands);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			execute_commands(commands, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}

int	is_builtin(t_mini *n)
{
	int		l;

	if (!n->toks)
		return (0);
	if ((n->toks && ft_strchr(*n->toks, '/')) || (n->env && \
		ft_strchr(n->env, '/')))
		return (0);
	l = ft_strlen(*n->toks);
	if (!ft_strncmp(*n->toks, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->toks, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->toks, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*n->toks, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*n->toks, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*n->toks, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*n->toks, "exit", l) && l == 4)
		return (1);
	return (0);
}


