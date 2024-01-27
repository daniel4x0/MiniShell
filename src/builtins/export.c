/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:49:58 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 17:50:01 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_equalsign(char *argv, char **envp, int index)  //controlla per "=" (environment variables per export e unset)
{
	int	equal_sign;

	index = 0;
	equal_sign = ft_strchr_i(argv, '=');
	if (equal_sign == -1)
		return (-1);
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], argv, equal_sign + 1))
			return (1);
		index++;
	}
	return (0);
}

int	ft_export(t_commands *commands)
{
	int		ij[2];
	int		pos;
	char	**argv;

	ij[1] = 0;
	argv = ((t_mini *)commands->cmds->content)->toks;
	if (len_matrix(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = check_equalsign(argv[ij[0]], commands->envp, ij[1]);
			if (pos == 1)
			{
				free(commands->envp[ij[1]]);
				commands->envp[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				commands->envp = extend_matrix(commands->envp, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}
