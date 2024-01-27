
#include "../../includes/minishell.h"

extern int	g_status;

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current;

	count = 0;
	current = lst;
	if (current)
		count++;
	else
		return (0);
	while (current->next != 0)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	*full_trim(char const *str, int in_quotes_single, int in_quotes_double)
{
	char	*result;
	int		count;
	int		res; //index for trimmed string
	int		i;  //index for input string

	res = -1;
	i = 0;
	count = amount_of_space(str);
	if (!str || count == -1)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		in_quotes_single = (in_quotes_single + (!in_quotes_double && str[i] == '\'')) % 2;
		in_quotes_double = (in_quotes_double + (!in_quotes_single && str[i] == '\"')) % 2;
		if ((str[i] != '\"' || in_quotes_single) && (str[i] != '\'' || in_quotes_double) \
			&& ++res >= 0)
			result[res] = str[i];
		i++;
	}
	result[++res] = '\0';
	return (result);
}

char	*env_expander(t_commands *commands, char *str, int index)
{
	int	in_quote_single = 0;
	int	in_quote_double = 0;
	while (str && str[++index])
	{
		in_quote_single = (in_quote_single + (!in_quote_double && str[index] == '\'')) % 2;
		in_quote_double = (in_quote_double + (!in_quote_single && str[index] == '\"')) % 2;
		if (!in_quote_single && str[index] == '$' && str[index + 1] && \
			((strchr_mod(&str[index + 1], "/~%^{}:; ") && !in_quote_double) || \
			(strchr_mod(&str[index + 1], "/~%^{}:;\"") && in_quote_double)))
			return (env_expander(commands, toks_extract(commands, str, ++index), -1));
	}
	return (str);
}

void	*parse_input(char **args, t_commands *commands)
{
	int	exit;
	int	i;

	exit = 0;
	commands->cmds = node_refil(switch_matrix(commands, args), -1);
	if (!commands->cmds)
		return (commands);
	i = ft_lstsize(commands->cmds);
	g_status = builtin(commands, commands->cmds, &exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && exit)
	{
		ft_lstclear(&commands->cmds, free_content);
		return (NULL);
	}
	return (commands);
}


