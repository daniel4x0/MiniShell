/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:15:06 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 09:15:08 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

t_mini	*fd_out_a(t_mini *mini, char **args, int *i)
{
	char	*error;
	int		j;
	int		k;

	j = 1;
	k = 0;
	error = "syntax error";
	(*i)++;
	if (args[*i])
		mini->fdout = get_fd(args[*i], mini->fdout, j, k);
	if (!args[*i] || mini->fdout == -1)
	{
		*i = -1;
		if (mini->fdout != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (mini);
}

t_mini	*fd_out_b(t_mini *mini, char **args, int *i)
{
	char	*error;
	int		j;
	int		k;

	j = 1;
	k = 1;
	error = "syntax error";
	(*i)++;
	if (args[++(*i)])
		mini->fdout = get_fd(args[*i], mini->fdout, j, k);
	if (!args[*i] || mini->fdout == -1)
	{
		*i = -1;
		if (mini->fdout != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (mini);
}

t_mini	*fd_in_a(t_mini *mini, char **args, int *i)
{
	char	*error;
	int		j;
	int		k;

	j = 0;
	k = 0;
	error = "syntax error";
	(*i)++;
	if (args[*i])
		mini->fdin = get_fd(args[*i], mini->fdout, j, k);
	if (!args[*i] || mini->fdin == -1)
	{
		*i = -1;
		if (mini->fdin != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (mini);
}

t_mini	*fd_in_b(t_mini *mini, char **args, int *i)
{
	char	*str[2];
	char	*s[2];
	char	*error;

	str[0] = NULL;
	str[1] = NULL;
	s[0] = NULL;
	s[1] = "heredoc delimited by end of file";
	error = "syntax error";
	(*i)++;
	if (args[++(*i)])
	{
		s[0] = args[*i];
		mini->fdin = here_docs(str[0], str[1], s[0], s[1]);
	}
	if (!args[*i] || mini->fdin == -1)
	{
		*i = -1;
		if (mini->fdin != -1)
		{
			ft_putendl_fd(error, 2);
			g_status = 2;
		}
	}
	return (mini);
}