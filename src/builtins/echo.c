/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:43:42 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 12:43:44 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_list *cmd)
{
    char	**argv;
    t_mini	*node;
	int		newline;
	int		index;
    int     flag;
	
	index = 0;
	flag = 0;
	newline = 1;
	node = cmd->content;
	argv = node->toks;
	while (argv && argv[++index])
	{
		if (!flag && !ft_strncmp(argv[index], "-n", 2) && \
			(ft_countchar(argv[index], 'n') == \
			(int)(ft_strlen(argv[index]) - 1)))
			newline = 0;
		else
		{
			flag = 1;
			ft_putstr_fd(argv[index], 1);
			if (argv[index + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}
