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

int	amount_of_space(char const *str)  //calculate no. of space to be mallocated based on sq and dq
{
	int	count;
	int	i;
	int	in_quotes_double;
	int	in_quotes_single;

	i = 0;
	count = 0;
	in_quotes_double = 0;
	in_quotes_single = 0;
	while (str && str[i])
	{
		in_quotes_single = (in_quotes_single + (!in_quotes_double && str[i] == '\'')) % 2;
		in_quotes_double = (in_quotes_double + (!in_quotes_single && str[i] == '\"')) % 2;
		if ((str[i] == '\"' && !in_quotes_single) || (str[i] == '\'' && !in_quotes_double))
			count++;
		i++;
	}
	if (in_quotes_single || in_quotes_double)
		return (-1);
	return (count);
}

int open_mutable_quotes_flag(char *str, char *delimiter)
{
    int in_single_quote = 0;
    int in_double_quote = 0;
    int word_count = 0;
    int index = 0;

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

int open_quotes_flag(const char *command, char *delimeter)
{
    int token_start = 0;
    int word_count = 0;
    int flag = 0;
    int open_quote = 0;

    while (command[token_start] != '\0')
    {
        if (!ft_strchr(delimeter, command[token_start]))
        {
            word_count++;
            while ((!ft_strchr(delimeter, command[token_start]) || flag) && command[token_start] != '\0')
            {
                if (!open_quote && (command[token_start] == '\"' || command[token_start] == '\''))
                    open_quote = command[token_start];
                flag = (flag + (command[token_start] == open_quote)) % 2;
                open_quote *= flag != 0;
                token_start++;
            }
            if (flag)
                return (-1);
        }
        else
            token_start++;
    }
    return word_count;
}