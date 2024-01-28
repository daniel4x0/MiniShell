/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:38:15 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/28 15:38:17 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	read_line_and_update(char ***m, int fd)
{
	char	**trimmed;
	char	*store;
	char	*line;

	trimmed = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		store = ft_strtrim(line, "\n");
		free(line);
		trimmed = extend_matrix(trimmed, store);
		free(store);
	}
	free_matrix(m);
	*m = trimmed;
}

char	*here_string(char *str[2], size_t len, char *limit, char *warn)
{
	char	*temp;

	while (g_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len) \
		|| ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

void	*execute_commands(t_commands *commands, t_list *cmd)
{
	int		fd[2];

	cmd_extract(commands, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (mini_perror(PIPERR, NULL, 1));
	if (!check_to_fork(commands, cmd, fd))
		return (NULL);
	close(fd[1]);
	if (cmd->next && !((t_mini *)cmd->next->content)->fdin)
		((t_mini *)cmd->next->content)->fdin = fd[0];
	else
		close(fd[0]);
	if (((t_mini *)cmd->content)->fdin > 2)
		close(((t_mini *)cmd->content)->fdin);
	if (((t_mini *)cmd->content)->fdout > 2)
		close(((t_mini *)cmd->content)->fdout);
	return (NULL);
}
