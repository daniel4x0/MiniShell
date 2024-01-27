#include "../../includes/minishell.h"

extern int g_status;

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

char	*here_string(char *newstr, char *str, char *max, char *err)
{
	size_t len;
	char	*store;

	len = 0;
	while (g_status != 130 && (!newstr || ft_strncmp(newstr, max, len) \
		|| ft_strlen(max) != len))
	{
		store = str;
		str = ft_strjoin(str, newstr);
		free(store);
		free(newstr);
		newstr = readline("> ");
		if (!newstr)
		{
			printf("%s (wanted `%s\')\n", err, max);
			break ;
		}
		store = newstr;
		newstr = ft_strjoin(newstr, "\n");
		free(store);
		len = ft_strlen(newstr) - 1;
	}
	free(newstr);
	return (str);
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