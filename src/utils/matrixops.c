/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:38:07 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 11:38:10 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_matrix(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}

char	**swap_matrix(char ***args, char **swap, int index)
{
	char	**store;
	int		i;
	int		sw;
	int		st;

	i = -1;
	sw = -1;
	st = -1;
	if (!args || !*args || index < 0 || index >= len_matrix(*args))
		return (NULL);
	store = ft_calloc(len_matrix(*args) + len_matrix(swap), sizeof(char *));
	while (store && args[0][++i])
	{
		if (i != index)
			store[++st] = ft_strdup(args[0][i]);
		else
		{
			while (swap && swap[++sw])
				store[++st] = ft_strdup(swap[sw]);
		}
	}
	free_matrix(args);
	*args = store;
	return (*args);
}


char	**switch_matrix(t_commands *commands, char **args)
{
	char	**swap;
	int		index;

	index = -1;
	while (args && args[++index])
	{
		args[index] = env_expander(commands, args[index], -1);
		args[index] = handle_env_tilde(args[index], \
			get_env_char("HOME", commands->envp, 4), 1);
		swap = tokenize_mutable_commands(args[index], "<|>");
		swap_matrix(&args, swap, index);
		index += len_matrix(swap) - 1;
		free_matrix_d(swap);
	}
	return (args);
}
