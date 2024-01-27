/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:53:17 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 10:53:19 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

extern int	g_status;

void	cmd_extract(t_commands *commands, t_list *cmd, char **str, char *path)
{
	t_mini	*mini;
	DIR		*directory;

	mini = cmd->content;
	directory = check_cmd(commands, cmd, &str, path);
	if (!is_builtin(mini) && mini && mini->toks && directory)
		mini_perror(IS_DIR, *mini->toks, 126);
	else if (!is_builtin(mini) && mini && mini->env && \
		access(mini->env, F_OK) == -1)
		mini_perror(NDIR, mini->env, 127);
	else if (!is_builtin(mini) && mini && mini->env && \
		access(mini->env, X_OK) == -1)
		mini_perror(NPERM, mini->env, 126);
	if (directory)
		closedir(directory);
	free_matrix(&str);
}

char	*get_env_char(char *env, char **envp, int n)
{
	int	i;
	int	j;

	i = 0;
	if (n < 0)
		n = ft_strlen(env);
	while (!ft_strchr(env, '=') && envp && envp[i])
	{
		j = n;
		if (j < ft_strchr_i(envp[i], '='))
			j = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], env, j))
			return (ft_substr(envp[i], j + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

void	get_pid(t_commands *commands)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		free_matrix(&commands->envp);
		exit(1);
	}
	if (!pid)
	{
		free_matrix(&commands->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	commands->pid = pid - 1;
}

void	*run_lexer(char *input, t_commands *commands)
{
	char	**token;
	t_mini	*mini;

	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	if (input[0] != '\0')
		add_history(input);
	token = tokenize_commands(input, " ");
	free(input);
	if (!token)
		mini_perror(QUOTE, NULL, 1);
	if (!token)
		return ("");
	commands = parse_input(token, commands);
	if (commands && commands->cmds)
		mini = commands->cmds->content;
	if (commands && commands->cmds && mini && mini->toks \
		&& ft_lstsize(commands->cmds) == 1)
		commands->envp = set_env_char("_", \
		mini->toks[len_matrix(mini->toks) - 1], commands->envp, 1);
	if (commands && commands->cmds)
		ft_lstclear(&commands->cmds, free_content);
	return (commands);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_commands	commands;

	(void)argc;
	(void)argv;
	commands = initialize_commands(argv, envp);
	while (envp != NULL)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline("shell>>  ");
		if (!run_lexer(input, &commands))
			break ;
	}
	exit(g_status);
}
