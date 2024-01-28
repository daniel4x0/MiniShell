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

int	check_equalsign(char *argv, char **envp, int index[2])
{
	int	equal_sign;

	index[1] = 0;
	equal_sign = ft_strchr_i(argv, '=');
	if (equal_sign == -1)
		return (-1);
	while (envp[index[1]])
	{
		if (!ft_strncmp(envp[index[1]], argv, equal_sign + 1))
			return (1);
		index[1]++;
	}
	return (0);
}

int	ft_export(t_commands *commands)
{
	int		index[2];
	int		flag;
	char	**argv;

	argv = ((t_mini *)commands->cmds->content)->toks;
	if (len_matrix(argv) >= 2)
	{
		index[0] = 1;
		while (argv[index[0]])
		{
			flag = check_equalsign(argv[index[0]], commands->envp, index);
			if (flag == 1)
			{
				free(commands->envp[index[1]]);
				commands->envp[index[1]] = ft_strdup(argv[index[0]]);
			}
			else if (!flag)
				commands->envp = extend_matrix(commands->envp, argv[index[0]]);
			index[0]++;
		}
	}
	return (0);
}
