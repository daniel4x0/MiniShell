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
	int	in_quotes_double;
	int	in_quotes_single;
    //int arr[2];

	i = 0;
	count = 0;
	in_quotes_double = 0;
	in_quotes_single = 0;
	while (str && str[i])
	{
		in_quotes_single = (in_quotes_single + \
        (!in_quotes_double && str[i] == '\'')) % 2;
		in_quotes_double = (in_quotes_double + \
        (!in_quotes_single && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !in_quotes_single) \
        || (str[i] == '\'' && !in_quotes_double))
			count++;
		i++;
	}
	if (in_quotes_single || in_quotes_double)
		return (-1);
	return (count);
}

int open_mutable_quotes_flag(char *str, char *delimiter)
{
    int in_single_quote;
    int in_double_quote;
    int word_count;
    int index;

    in_single_quote = 0;
    in_double_quote = 0;
    word_count = 0;
    index = 0;
    while (str && str[index] != '\0')
    {
        word_count++;

        if (!ft_strchr(delimiter, str[index]))
        {
            while ((!ft_strchr(delimiter, str[index]) || in_single_quote || in_double_quote) && str[index] != '\0')
            {
                in_single_quote = (in_single_quote + (!in_double_quote && str[index] == '\'')) % 2;
                in_double_quote = (in_double_quote + (!in_single_quote && str[index] == '\"')) % 2;
                index++;
            }

            if (in_single_quote || in_double_quote)
                return (-1);
        }
        else
            index++;
    }

    return (word_count);
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