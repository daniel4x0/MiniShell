/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 08:20:26 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 08:20:28 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

int	here_docs(char *newstr, char *str, char *delimeter, char *err)
{
	int		fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}
	str = get_here_str(newstr, str, 0, delimeter, err);
	write(fd[1], str, ft_strlen(str));
	free(str);
	close(fd[1]);
	if (g_status == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}