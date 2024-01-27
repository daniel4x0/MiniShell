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
	int		index;
	int		swap;

	index = 0;
	swap = 0;
	argv = ((t_mini *)commands->cmds->content)->toks;
	if (len_matrix(argv) >= 2)
	{
		while (argv[++index])
		{
			if (argv[index][ft_strlen(argv[index]) - 1] != '=')
			{
				store = ft_strjoin(argv[index], "=");
				free(argv[index]);
				argv[index] = store;
			}
			if (check_equalsign(argv[index], commands->envp, swap))
				swap_matrix(&commands->envp, NULL, swap);
		}
	}
	return (0);
}
