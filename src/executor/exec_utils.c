#include  "../../includes/minishell.h"

int find_env_index(char **env, const char *var) 
{
    int index = 0;
    while (env[index] != NULL) {
        if (strncmp(env[index], var, strlen(var)) == 0 && env[index][strlen(var)] == '=') {
            return index;
        }
        index++;
    }
    return -1;
}

int find_binary_path(t_mini *mini, t_cmds *cmds) 
{
    int index = 0;
    while (mini->env[index] != NULL) 
    {
        if (strncmp(mini->env[index], "PATH=", 5) == 0) 
        {
            char *path = mini->env[index] + 5;
            char *token = strtok(path, ":");
            while (token != NULL) 
            {
                char *full_path = malloc(strlen(token) + strlen(cmds->cmd) + 2);
                if (full_path == NULL) 
                {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                sprintf(full_path, "%s/%s", token, cmds->cmd);
                if (access(full_path, X_OK) == 0) 
                {
                    return index;
                }
                free(full_path);
                token = strtok(NULL, ":");
            }
        }
        index++;
    }
    return -1;
}

char *add_path_to_command(t_mini *mini, t_cmds *cmds, int index)  
{
    char *path = mini->env[index] + 5;
    char *full_path = malloc(strlen(path) + strlen(cmds->cmd) + 2);
    if (full_path == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    sprintf(full_path, "%s/%s", path, cmds->cmd);
    return full_path;
} 

void execute(t_mini *mini, t_cmds *cmds) 
{
    int index = find_binary_path(mini, cmds);
    if (index != -1)
    {
        char *full_path = add_path_to_command(mini, cmds, index);
        printf("%s\n", full_path);

        // Handle redirection
        if (cmds->redirect_count > 0)
        {
            for (int i = 0; i < cmds->redirect_count; i++)
            {
                if (cmds->redirect[i].redirect_type == 1)
                {
                    // Output redirection (>)
                    int fdout = open(cmds->redirect[i].outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    if (fdout == -1)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fdout, STDOUT_FILENO);
                    close(fdout);
                }
                else if (cmds->redirect[i].redirect_type == 2)
                {
                    // Output redirection (>>)
                    int fdout = open(cmds->redirect[i].outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
                    if (fdout == -1)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fdout, STDOUT_FILENO);
                    close(fdout);
                }
                else if (cmds->redirect[i].redirect_type == 3)
                {
                    // Input redirection (<)
                    int fdin = open(cmds->redirect[i].infile, O_RDONLY);
                    if (fdin == -1)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fdin, STDIN_FILENO);
                    close(fdin);
                }
            }
        }

        execve(full_path, mini->toks, mini->env);
        perror("execve");
    }
    else 
    {
        fprintf(stderr, "Error: Command not found\n");
        exit(EXIT_FAILURE);
    }
}

// Function to execute a command using execve after checking whether it's a built-in command or an external binary
/*void execute(t_mini *mini, t_cmds *cmds) 
{
    int index = find_binary_path(mini, cmds);
    if (index != -1)
    {
        char *full_path = add_path_to_command(mini, cmds, index);
        //char *full_path = find_path(mini, mini->env);
        printf("%s\n", full_path);
        execve(full_path, mini->toks, mini->env);
        perror("execve");
        //free(full_path);
    }
    else 
    {
        fprintf(stderr, "Error: Command not found\n");
        exit(EXIT_FAILURE);
    }
}*/

void    porcodio(t_mini *mini)
{
    char *full_path = find_path(mini, mini->env);
    while (mini->env)
    {
        execve(full_path, mini->toks, mini->env);
        perror("Execve failed");
		exit(EXIT_FAILURE);
    }
}
void handle_here_document(t_mini *mini, const char *delimiter) 
{
    (void)mini;
    char *line = NULL;
    size_t len = 0;

    while (1) 
    {
        printf("<< ");
        ssize_t read_bytes = getline(&line, &len, stdin);
        if (read_bytes == -1) 
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (strcmp(line, delimiter) == 0) 
        {
            break;
        }
    }

    free(line);
}

// Function to handle input (<) and output (>, >>) redirection
void handle_redirection(t_mini *mini, t_cmds *current_cmd) 
{
    current_cmd->redirect->infile = (char *)malloc(sizeof(char *) * 1000);
    current_cmd->redirect->outfile = (char *)malloc(sizeof(char *) * 1000);
    //printf("porcodio\n");
    if (current_cmd->redirect->infile != NULL) 
    {
        //current_cmd->redirect->infile = (char *)malloc(sizeof(char *) * 1000);
        mini->fdin = open(current_cmd->redirect->infile, O_RDONLY);
        if (mini->fdin == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    if (current_cmd->redirect->outfile != NULL) 
    {
        //current_cmd->redirect->infile = (char *)malloc(sizeof(char *) * 1000);
        //printf("porcodio\n");
        int flags;
        if (current_cmd->redirect->redirect_type == 1) 
        {
            flags = O_WRONLY | O_CREAT | O_TRUNC;
        }
        else
        {
            flags = O_WRONLY | O_CREAT | O_APPEND;
        }

        mini->fdout = open(current_cmd->redirect->outfile, flags, 0666);
        if (mini->fdout == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }
}

// Function to update file descriptors based on redirection information
void update_file_descriptors(t_mini *mini, t_cmds *current_cmd)
{
    if (current_cmd->fdi != -1)
    {
        dup2(current_cmd->fdi, STDIN_FILENO);
        close(current_cmd->fdi);
    }
    else 
    {
        dup2(mini->fdin, STDIN_FILENO);
        close(mini->fdin);
    }

    if (current_cmd->fdo != -1) 
    {
        dup2(current_cmd->fdo, STDOUT_FILENO);
        close(current_cmd->fdo);
    } 
    else 
    {
        dup2(mini->fdout, STDOUT_FILENO);
        close(mini->fdout);
    }
}

// Function to close file descriptors related to input and output
void close_file_descriptors(t_mini *mini) 
{
    close(mini->fdin);
    close(mini->fdout);
}

// Function to execute multiple commands in a pipeline
void execute_pipeline(t_mini *mini) 
{
    t_cmds *cmd = initialize_cmds();
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);
    int pipe_fd[2];

    while (cmd)
    {
        if (cmd->next)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            cmd->fdo = pipe_fd[1];
            cmd->next->fdi = pipe_fd[0];
        }

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            //close_file_descriptors(mini);
            //update_file_descriptors(mini, cmd);
            //execute(mini, cmd);
            porcodio(mini);
        }
        else
        {
            close(cmd->fdo);
            if (!cmd->next)
            {
                close(cmd->fdi);
            }
            waitpid(pid, NULL, 0);
        }

        cmd = cmd->next;
    }

    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);

    close(saved_stdin);
    close(saved_stdout);
}

// Main execution function
void execute_commands(t_mini *mini)
{
    t_cmds *cmd = initialize_cmds();
    while (cmd)
    {
        if (cmd->redirect && cmd->redirect->redirect_type == 3)
        {
            handle_here_document(mini, cmd->redirect->infile);
            cmd = cmd->next;
            continue;
        }

        handle_redirection(mini, cmd);

        execute_pipeline(mini);

        cmd = cmd->next;
    }
}