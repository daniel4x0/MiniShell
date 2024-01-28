/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 06:59:27 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 06:59:29 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

char	**handle_mutable_quotes(char **result, char *str, char *delimeter)
{
	int		in_quotes_single = 0;
	int		in_quotes_double = 0;
	int		index = 0;
	int		start = 0;
	int		flag = 0;

	while (str && str[index] != '\0')
	{
		start = index;
		if (!ft_strchr(delimeter, str[index]))
		{
			while ((!ft_strchr(delimeter, str[index]) || in_quotes_single || in_quotes_double) && str[index])
			{
				in_quotes_single = (in_quotes_single + (!in_quotes_double && str[index] == '\'')) % 2;
				in_quotes_double = (in_quotes_double + (!in_quotes_single && str[index] == '\"')) % 2;
				index++;
			}
		}
		else
			index++;
		result[flag++] = ft_substr(str, start, index - start);
	}
	return (result);
}

char	**handle_quotes(char **result, char const *s, char *set, int i[3])
{
	int		len;
	int in_quotes_single = 0;
	int in_quotes_double = 0;

	len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || in_quotes_single || in_quotes_double) && s[i[0]])
		{
			in_quotes_single = (in_quotes_single + (!in_quotes_double && s[i[0]] == '\'')) % 2;
			in_quotes_double = (in_quotes_double + (!in_quotes_single && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			result[i[2]++] = "\0";
		else
			result[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (result);
}

char	**tokenize_mutable_commands(char const *str, char *delimeter)
{
	char	**result;
	int		word_count;
	
	if (!str)
		return (NULL);
	word_count = open_mutable_quotes_flag((char *)str, delimeter);
	if (word_count == -1)
		return (NULL);
	result = malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = handle_mutable_quotes(result, (char *)str, delimeter);
	result[word_count] = NULL;
	return (result);
}

char	**tokenize_commands(char const *str, char *delimeter)
{
	char	**result;
	int		word_count;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!str)
		return (NULL);
	word_count = open_quotes_flag(str, delimeter, counts);
	if (word_count == -1)
		return (NULL);
	result = malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = handle_quotes(result, str, delimeter, i);
	result[word_count] = NULL;
	return (result);
}
