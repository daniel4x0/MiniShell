/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:14:32 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 14:14:34 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	cd_error(char **mx1, char **mx2)
{
	DIR		*directory;

	directory = NULL;
	if (mx1[1])
		directory = opendir(mx1[1]);
	if (!mx1[1] && mx2[0] && !mx2[0][0])
	{
		g_status = 1;
		ft_putstr_fd("home not set\n", 2);
	}
	if (mx2[0] && !mx1[1])
		g_status = chdir(mx2[0]) == -1;
	if (mx1[1] && directory && access(mx1[1], F_OK) != -1)
		chdir(mx1[1]);
	else if (mx1[1] && access(mx1[1], F_OK) == -1)
		mini_perror(NDIR, mx1[1], 1);
	else if (mx1[1])
		mini_perror(NOT_DIR, mx1[1], 1);
	if (mx1[1] && directory)
		closedir(directory);
}

int	ft_cd(t_commands *commands)
{
    char    **mx1;  //store command
    char    **mx2;  //store additional command
	char	*env;

	g_status = 0;
	mx1 = ((t_mini *)commands->cmds->content)->toks;
	env = get_env_char("HOME", commands->envp, 4);
	if (!env)
		env = ft_strdup("");
	mx2 = extend_matrix(NULL, env);
	free(env);
	env = getcwd(NULL, 0);
	mx2 = extend_matrix(mx2, env);
	free(env);
	cd_error(mx1, mx2);
	if (!g_status)
		commands->envp = set_env_char("OLDPWD", mx2[1], commands->envp, 6);
	env = getcwd(NULL, 0);
	if (!env)
		env = ft_strdup("");
	mx2 = extend_matrix(mx2, env);
	free(env);
	commands->envp = set_env_char("PWD", mx2[2], commands->envp, 3);
	free_matrix(&mx2);
	return (g_status);
}
