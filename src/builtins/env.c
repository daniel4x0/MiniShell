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
	int		im[2];
	char	*ev_evv[2];

	if (n < 0)
		n = ft_strlen(var);
	im[0] = -1;
	ev_evv[0] = ft_strjoin(var, "=");
	ev_evv[1] = ft_strjoin(ev_evv[0], value);
	free(ev_evv[0]);
	while (!ft_strchr(var, '=') && envp && envp[++im[0]])
	{
		im[1] = n;
		if (im[1] < ft_strchr_i(envp[im[0]], '='))
			im[1] = ft_strchr_i(envp[im[0]], '=');
		if (!ft_strncmp(envp[im[0]], var, im[1]))
		{
			ev_evv[0] = envp[im[0]];
			envp[im[0]] = ev_evv[1];
			free(ev_evv[0]);
			return (envp);
		}
	}
	envp = extend_matrix(envp, ev_evv[1]);
	free(ev_evv[1]);
	return (envp);
}
