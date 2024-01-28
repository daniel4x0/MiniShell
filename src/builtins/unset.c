/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:34:18 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 17:34:21 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_commands *commands)
{
	char	**argv;
	char	*store;
	int		index[2];

	index[0] = 0;
	argv = ((t_mini *)commands->cmds->content)->toks;
	if (len_matrix(argv) >= 2)
	{
		while (argv[++index[0]])
		{
			if (argv[index[0]][ft_strlen(argv[index[0]]) - 1] != '=')
			{
				store = ft_strjoin(argv[index[0]], "=");
				free(argv[index[0]]);
				argv[index[0]] = store;
			}
			if (check_equalsign(argv[index[0]], commands->envp, index))
				swap_matrix(&commands->envp, NULL, index[1]);
		}
	}
	return (0);
}
