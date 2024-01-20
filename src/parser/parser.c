#include "../../includes/minishell.h"

t_parse *initialize_parser()
{
    t_parse *parser = (t_parse *)malloc(sizeof(t_parse));
    if (parser == NULL)
    {
        exit(EXIT_FAILURE);
    }

    parser->toks = 0;
    parser->p_args = 0;
    parser->red = 0;
    parser->args = 0;

    return parser;
}

int open_next_file(const char *filename) 
{
    int fd;

    if (strcmp(filename, "<") == 0) 
    {
        fprintf(stderr, "Error: Missing input file after '<'\n");
        exit(EXIT_FAILURE);
    } else if (strcmp(filename, ">") == 0)
    {
        fprintf(stderr, "Error: Missing output file after '>'\n");
        exit(EXIT_FAILURE);
    } else if (strcmp(filename, ">>") == 0) 
    {
        fprintf(stderr, "Error: Missing output file after '>>'\n");
        exit(EXIT_FAILURE);
    }

    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    return fd;
}

int is_redirection(char *str) 
{
    return (str && (str[0] == '<' || str[0] == '>' || (str[1] && str[1] == '>')));
}

int count_total_redirection(t_mini *mini, int i) 
{
    while (mini->toks[i] && is_redirection(mini->toks[i])) 
    {
        i++;
    }
    return i;
}

int count_total_args(t_mini *mini, t_parse *parser) 
{
    int count = 0;
    while (mini->toks[parser->args] && !is_redirection(mini->toks[parser->args]) && strcmp(mini->toks[parser->args], "|") != 0) 
    {
        parser->args++;
        count++;
    }
    return count;
}

int count_redirection_toks(t_mini *mini, t_parse *parser) 
{
    int count = 0;
    while (mini->toks[parser->red] && is_redirection(mini->toks[parser->red])) 
    {
        parser->red++;
        count++;
    }
    return count;
}

int	handle_redirection_1(t_mini *mini, char **toks, t_parse *parser, int i) //(>, >>)
{
    //cmds = initialize_cmds();
	if (!toks[parser->toks + 1] || ft_strncmp(toks[parser->toks + 1], "|", 1) == 0)
	{
		printf("Error: Missing argument for redirection.\n");
		return (-1);
	}
	if (toks[parser->toks + 1][0] == '>' || toks[parser->toks + 1][0] == '<')
		parser->toks++;
	else
	{
		mini->cmds->redirect[mini->cmds->redirect_count].outfile
			= ft_strdup(toks[parser->toks + 1]);
		mini->cmds->redirect[mini->cmds->redirect_count].redirect_type = i;
		mini->cmds->redirect_count++;
		mini->cmds->fdo = 1;
		parser->toks += 2;
	}
    //printf("%s\n", cmds->redirect->outfile);
	return (parser->toks);
}

int	handle_redirection_2(t_mini *mini, char **toks, t_parse *parser, int i)
{
	if (!toks[parser->toks + 1] || ft_strncmp(toks[parser->toks + 1], "|", 1) == 0)
	{
		printf("Error: Missing argument for redirection.\n");
		return (-1);
	}
	if (toks[parser->toks + 1][0] == '>' || toks[parser->toks + 1][0] == '<')
		parser->toks++;
	else
	{
		mini->cmds->redirect[mini->cmds->redirect_count].infile
			= ft_strdup(toks[parser->toks + 1]);
		mini->cmds->redirect[mini->cmds->redirect_count].redirect_type = i;
		mini->cmds->redirect_count++;
		mini->cmds->fdi = 1;
		parser->toks += 2;
    }
	return (parser->toks);
}

// Function to handle adding the last command in the command sequence to the cmds structure
void	handle_last_command(t_mini *mini, t_parse *parser)
{
    printf("entered handle last command fucntion\n");
    //initialize_cmds();
	mini->cmds->cmd = (char *)malloc(sizeof(char *) * 1000);
    mini->cmds->args = (char **)malloc(sizeof(char **) * 1000);
	if (mini->cmds->cmd == NULL)
	{
        printf("cmd is null\n");
		mini->cmds->cmd = ft_strdup(mini->toks[parser->toks]);
		mini->cmds->args[0] = ft_strdup(mini->toks[parser->toks]);
		parser->toks++;
	}
	else
	{
		while (mini->toks[parser->toks]
			&& ft_strncmp(mini->toks[parser->toks], "|", 1)
			&& !is_redirection(mini->toks[parser->toks]))
		{
			mini->cmds->args[parser->p_args] = ft_strdup(mini->toks[parser->toks]);
			parser->toks++;
		}
	}
	parser->p_args++;
	mini->cmds->args[parser->p_args] = NULL;
}

t_cmds *create_new_command() 
{
    t_cmds *new_cmd = malloc(sizeof(t_cmds));
    if (!new_cmd) 
    {
        exit(EXIT_FAILURE);
    }

    new_cmd->redirect = NULL;
    new_cmd->next = NULL;

    return new_cmd;
}

int parse_input(t_mini *mini) 
{
    printf("enters parse function\n");
    t_cmds *head = initialize_cmds();
    t_cmds *current = head;
    t_parse *parser = initialize_parser();
    int i = 0;

    while (mini->toks[i]) 
    {
        if (strcmp(mini->toks[i], "|") == 0) 
        {
            current->next = initialize_cmds();
            current = current->next;
            parser->args++;
        } 
        else if (is_redirection(mini->toks[i])) 
        {
            if (mini->toks[i][0] == '>') 
            {
                //printf("porcodio\n");
                i = handle_redirection_1(mini, mini->toks, parser, i);
            } 
            else if (mini->toks[i][0] == '<') 
            {
                i = handle_redirection_2(mini, mini->toks, parser, i);
            }

            if (i == -1) 
            {
                return -1;
            }
        } 
        else
        {
            printf("trying to enter handle last command fucntion\n");
            handle_last_command(mini, parser);
        }

        i++;
    }
    return 1;
}