/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaruso <ecaruso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:57:44 by grinella          #+#    #+#             */
/*   Updated: 2024/01/06 02:01:56 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_mini *initialize_mini()
{
    t_mini *mini = malloc(sizeof(t_mini));
    if (!mini)
    {
        perror("Brutto STronzo");
        exit(EXIT_FAILURE);
    }

    mini->cmds = initialize_cmds();
    mini->fdin = STDIN_FILENO;
    mini->fdout = STDOUT_FILENO;
    //mini->env = envp;
    mini->toks = 0;
    mini->toks_count = 0;
    mini->args = 0;
    mini->redirect = 0;

    return mini;
}

t_cmds *initialize_cmds()
{
    t_cmds *cmds = (t_cmds *)malloc(sizeof(t_cmds) * 1);
    if (cmds == NULL)
    {
        exit(EXIT_FAILURE);
    }

    //cmds->cmd = (char *)malloc(sizeof(char *) * 1000);
    //cmds->args = (char **)malloc(sizeof(char **) * 1000);
    cmds->redirect = (t_redirect *)malloc(sizeof(t_redirect));
    if (cmds->redirect == NULL)
    {
        exit(EXIT_FAILURE);
    }
    cmds->cmd = NULL;
    cmds->args = NULL;
    cmds->redirect->infile = (char *)malloc(sizeof(char *) * 1000);
    cmds->redirect->outfile = (char *)malloc(sizeof(char *) * 1000);
    //cmds->redirect->infile = NULL;
    //cmds->redirect->outfile = NULL;
    cmds->redirect->redirect_type = 0;
    cmds->fdi = 0;
    cmds->fdo = 0;
    cmds->redirect_count = 0;
    cmds->next = NULL;

    return cmds;
}

void free_cmd(t_cmds *cmd)
{
    free(cmd->cmd);
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i] != NULL; i++) //norminette for to while
        {
            free(cmd->args[i]);
        }
        free(cmd->args);
    }
    if (cmd->redirect)
    {
        free(cmd->redirect->infile);
        free(cmd->redirect->outfile);
        free(cmd->redirect);
    }
    free(cmd);
}


int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
	const char	*input;
	t_mini	*mini = initialize_mini();
    //t_cmds  *cmd = initialize_cmds();
	//int		i;

    //initialize_mini(envp);
	get_env(envp, mini);
	while (1)
	{
		input = readline("shell>> ");
        if (input && input[0])
        {
            printf("enters main function\n");
            add_history(input);
        }
        if (input && input[0])
		{
            if (run_lexer(input, mini) && parse_input(mini))
		    {
                printf("parse and lex successful\n");
                execute_commands(mini);
		    }
        }
		//free_cmds(&mini, input);
	}
	return (0);
}


