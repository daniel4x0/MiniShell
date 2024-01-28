/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 06:49:47 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 06:49:49 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	amount_of_space(char const *str)
{
	int	count;
	int	i;
	int	arr[2];

	i = 0;
	count = 0;
	arr[DQ] = 0;
	arr[SQ] = 0;
	while (str && str[i])
	{
		arr[SQ] = (arr[SQ] + (!arr[DQ] && str[i] == '\'')) % 2;
		arr[DQ] = (arr[DQ] + (!arr[SQ] && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !arr[SQ]) || (str[i] == '\'' && !arr[DQ]))
			count++;
		i++;
	}
	if (arr[SQ] || arr[DQ])
		return (-1);
	return (count);
}

int	open_mutable_quotes_flag(char *str, char *delimiter)
{
	int	wc_i[2];
	int	arr[2];

	arr[0] = 0;
	arr[1] = 0;
	wc_i[0] = 0;
	wc_i[1] = 0;
	while (str && str[wc_i[1]] != '\0' && wc_i[0]++)
	{
		if (!ft_strchr(delimiter, str[wc_i[1]]))
		{
			while ((!ft_strchr(delimiter, str[wc_i[1]]) \
			|| arr[SQ] || arr[DQ]) && str[wc_i[1]] != '\0')
			{
				arr[SQ] = (arr[SQ] + (!arr[DQ] && str[wc_i[1]] == '\'')) % 2;
				arr[DQ] = (arr[DQ] + (!arr[SQ] && str[wc_i[1]] == '\"')) % 2;
				wc_i[1]++;
			}
			if (arr[SQ] || arr[DQ])
				return (-1);
		}
		else
			wc_i[1]++;
	}
	return (wc_i[0]);
}

int	open_quotes_flag(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}
