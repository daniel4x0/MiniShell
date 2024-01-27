/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:42:56 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/26 21:42:57 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**set_env_char(char *var, char *value, char **envp, int n)
{
	int		index;
	int		max_index;
	char	*env_var;
	char	*env_var_value;

	if (n < 0)
		n = ft_strlen(var);
	index = -1;
	env_var = ft_strjoin(var, "=");
	env_var_value = ft_strjoin(env_var, value);
	free(env_var);
	while (!ft_strchr(var, '=') && envp && envp[++index])
	{
		max_index = n;
		if (max_index < ft_strchr_i(envp[index], '='))
			max_index = ft_strchr_i(envp[index], '=');
		if (!ft_strncmp(envp[index], var, max_index))
		{
			env_var = envp[index];
			envp[index] = env_var_value;
			free(env_var);
			return (envp);
		}
	}
	envp = extend_matrix(envp, env_var_value);
	free(env_var_value);
	return (envp);
}



