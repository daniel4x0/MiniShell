/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:27:47 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/28 17:27:49 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

char	*full_trim(char const *str, int sq, int dq)
{
	char	*result;
	int		count;
	int		res;
	int		i;

	res = -1;
	i = 0;
	count = amount_of_space(str);
	if (!str || count == -1)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		sq = (sq + (!dq && str[i] == '\'')) % 2;
		dq = (dq + (!sq && str[i] == '\"')) % 2;
		if ((str[i] != '\"' || sq) && (str[i] != '\'' || dq) \
			&& ++res >= 0)
			result[res] = str[i];
		i++;
	}
	result[++res] = '\0';
	return (result);
}

char	*env_expander(t_commands *commands, char *str, int index)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (str && str[++index])
	{
		sq = (sq + (!dq && str[index] == '\'')) % 2;
		dq = (dq + (!sq && str[index] == '\"')) % 2;
		if (!sq && str[index] == '$' && str[index + 1] && \
			((strchr_mod(&str[index + 1], "/~%^{}:; ") && !dq) || \
			(strchr_mod(&str[index + 1], "/~%^{}:;\"") && dq)))
			return (env_expander(commands, \
			toks_extract(commands, str, ++index), -1));
	}
	return (str);
}

void	*parse_input(char **args, t_commands *commands)
{
	int	exit;
	int	i;

	exit = 0;
	commands->cmds = node_refil(switch_matrix(commands, args), -1);
	if (!commands->cmds)
		return (commands);
	i = ft_lstsize(commands->cmds);
	g_status = builtin(commands, commands->cmds, &exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && exit)
	{
		ft_lstclear(&commands->cmds, free_content);
		return (NULL);
	}
	return (commands);
}
