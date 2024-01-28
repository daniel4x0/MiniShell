/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:33:19 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 09:33:20 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_cmd(char **env_path, char *cmd, char *full_path)
{
	char	*store;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		store = ft_strjoin(env_path[i], "/");
		if (!store)
			return (NULL);
		full_path = ft_strjoin(store, cmd);
		free(store);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

DIR	*check_cmd(t_commands *commands, t_list *cmd, char ***s, char *path)
{
	t_mini	*mini;
	DIR		*directory;

	directory = NULL;
	mini = cmd->content;
	if (mini && mini->toks)
		directory = opendir(*mini->toks);
	if (mini && mini->toks && ft_strchr(*mini->toks, '/') && !directory)
	{
		*s = ft_split(*mini->toks, '/');
		mini->env = ft_strdup(*mini->toks);
		free(mini->toks[0]);
		mini->toks[0] = ft_strdup(s[0][len_matrix(*s) - 1]);
	}
	else if (!is_builtin(mini) && mini && mini->toks && !directory)
	{
		path = get_env_char("PATH", commands->envp, 4);
		*s = ft_split(path, ':');
		free(path);
		mini->env = find_cmd(*s, *mini->toks, mini->env);
		if (!mini->env || !mini->toks[0] || !mini->toks[0][0])
			mini_perror(NCMD, *mini->toks, 127);
	}
	return (directory);
}

t_mini	*handle_pipe_redir(t_mini *mini, char **store1, char **store2, int *i)
{
	if (store1[*i])
	{
		if (store1[*i][0] == '>' && store1[*i + 1] && store1[*i + 1][0] == '>')
			mini = fd_out_b(mini, store2, i);
		else if (store1[*i][0] == '>')
			mini = fd_out_a(mini, store2, i);
		else if (store1[*i][0] == '<' && store1[*i + 1] && \
			store1[*i + 1][0] == '<')
			mini = fd_in_b(mini, store2, i);
		else if (store1[*i][0] == '<')
			mini = fd_in_a(mini, store2, i);
		else if (store1[*i][0] != '|')
			mini->toks = extend_matrix(mini->toks, store2[*i]);
		else
		{
			mini_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (mini);
	}
	mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (mini);
}

char	**trim_dump(char **args)
{
	char	**store;
	char	*result;
	int		j;

	j = -1;
	store = dup_matrix(args);
	while (store && store[++j])
	{
		result = full_trim(store[j], 0, 0);
		free(store[j]);
		store[j] = result;
	}
	return (store);
}
