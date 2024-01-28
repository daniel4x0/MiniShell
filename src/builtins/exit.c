/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 06:26:21 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 06:26:23 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_list *cmd, int *exit, long i)
{
	t_mini	*mini;
	long	j;

	mini = cmd->content;
	*exit = !cmd->next;
	if (*exit)
		ft_putstr_fd("exit\n", 2);
	if (!mini->toks || !mini->toks[1])
		return (0);
	j = ft_atoi2(mini->toks[1], &i);
	if (j == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(mini->toks[1], 2);
		ft_putstr_fd(": invalid insertion\n", 2);
		return (255);
	}
	else if (mini->toks[2])
	{
		*exit = 0;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	i %= 256 + 256 * (i < 0);
	return (i);
}
