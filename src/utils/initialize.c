/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:56:36 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 10:56:37 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

t_commands	initialize_env(t_commands commands, char *str, char **argv)
{
	char	*store;

	str = getcwd(NULL, 0);
	commands.envp = set_env_char("PWD", str, commands.envp, 3);
	free(str);
	str = get_env_char("SHLVL", commands.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		store = ft_strdup("1");
	else
		store = ft_itoa(ft_atoi(str) + 1);
	free(str);
	commands.envp = set_env_char("SHLVL", store, commands.envp, 5);
	free(store);
	str = get_env_char("PATH", commands.envp, 4);
	if (!str)
		commands.envp = set_env_char("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", commands.envp, 4);
	free(str);
	str = get_env_char("_", commands.envp, 1);
	if (!str)
		commands.envp = set_env_char("_", argv[0], commands.envp, 1);
	free(str);
	return (commands);
}

t_mini	*initialize_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->toks = NULL;
	mini->env = NULL;
	mini->fdin = STDIN_FILENO;
	mini->fdout = STDOUT_FILENO;
	return (mini);
}

t_commands	initialize_commands(char **argv, char **envp)
{
	t_commands	commands;
	char		*str;

	str = NULL;
	commands.cmds = NULL;
	commands.envp = dup_matrix(envp);
	g_status = 0;
	get_pid(&commands);
	commands = initialize_env(commands, str, argv);
	return (commands);
}

void	free_content(void *content)
{
	t_mini	*mini;

	mini = content;
	free_matrix(&mini->toks);
	free(mini->env);
	if (mini->fdin != STDIN_FILENO)
		close(mini->fdin);
	if (mini->fdout != STDOUT_FILENO)
		close(mini->fdout);
	free(mini);
}

t_list	*end_fill(t_list *cmds, char **args, char **store)
{
	ft_lstclear(&cmds, free_content);
	free_matrix(&store);
	free_matrix(&args);
	return (NULL);
}
