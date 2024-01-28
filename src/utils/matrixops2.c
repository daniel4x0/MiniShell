/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:43:53 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/25 11:43:56 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_matrix(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m && m[0])
	{
		free(m[0]);
		*m = NULL;
	}
}


void	free_matrix_d(char **m)
{
	int	i;

	i = -1;
	while (m[++i])
	{
		free(m[i]);
	}
	free(m);
}

char	**dup_matrix(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = len_matrix(m);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (m[i])
	{
		out[i] = ft_strdup(m[i]);
		if (!out[i])
		{
			free_matrix(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}

int	fd_putmatrix(char **m, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (nl)
			count += ft_putendl_fd(m[i], fd);
		else
			count += ft_putstr_fd(m[i], fd);
		i++;
	}
	return (count);
}

char	**extend_matrix(char **str, char *newstr)
{
	char	**result;
	int		len;
	int		i;

	i = -1;
	result = NULL;
	if (!newstr)
		return (str);
	len = len_matrix(str);
	result = malloc(sizeof(char *) * (len + 2));
	result[len + 1] = NULL;
	if (!result)
		return (str);
	while (++i < len)
	{
		result[i] = ft_strdup(str[i]);
		if (!result[i])
		{
			free_matrix(&str);
			free_matrix(&result);
		}
	}
	result[i] = ft_strdup(newstr);
	free_matrix(&str);
	return (result);
}
