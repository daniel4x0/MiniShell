#include "../../includes/minishell.h"

/*void execute_commands(t_mini *mini) {
    t_cmds *cmd = mini->cmds;
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    while (cmd) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (cmd->redirect) {
                if (cmd->redirect->infile) {
                    dup2(mini->fdin, STDIN_FILENO);
                    close(mini->fdin);
                }
                if (cmd->redirect->outfile) {
                    dup2(mini->fdout, STDOUT_FILENO);
                    close(mini->fdout);
                }
            }

            execvp(cmd->cmd, cmd->args);
            perror("Execvp failed");
            fprintf(stderr, "Command: %s\n", cmd->cmd);
            fprintf(stderr, "Arguments:\n");
            char **args = cmd->args;
            while (*args) {
                fprintf(stderr, "  %s\n", *args++);
            }
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("Exit Status: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Terminated by Signal: %d\n", WTERMSIG(status));
            } else {
                printf("Unknown termination\n");
            }
            //exit(EXIT_SUCCESS);
            
            }

        cmd = cmd->next;
    }
 
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);

    close(saved_stdin);
    close(saved_stdout);
}*/

char *find_path(t_mini *mini, char **env)
{
	struct stat buff;
	int		i;
	char	**base;
	char	*temp;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	base = ft_split((env[i] + 5), ':');
	i = -1;
	while(base && base[++i])
	{
		temp = ft_strjoin(base[i], "/");
		if (!lstat(ft_strjoin(temp, mini->toks[0]), &buff))
		{
			temp = ft_strjoin(temp, mini->toks[0]);
			return(temp);
		}
		free(temp);
	}
	free(temp);
	return(temp);
}

/*void execute_commands(t_mini *mini, char **env)
{
	//l'execve funziona ma la matrice con in comandi la creo in questa funzione (char **str) mentre dovrebbe essere
	//assegnata nel parser sulla variabile mini->toks
	int		status;
	char	*path;
	char	**str;
	pid_t	pid;

	path = find_path(mini, env);
	str = mini->cmds->args;
	pid = fork();
	if (pid == -1)
	{
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
	else if (pid == 0)
	{
		execve(path, str, env);
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("PORCODIO %d\n", WEXITSTATUS(status));
		else
			printf("PORCODIO\n");
	}
}*/

