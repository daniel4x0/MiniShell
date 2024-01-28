/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 06:57:26 by duzegbu           #+#    #+#             */
/*   Updated: 2024/01/27 06:57:27 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

char	*handle_env_tilde(char *str, char *tilde, int index)
{
	char	*path;
	char	*result;
	int		arr[2];

	index = -1;
	while (str && str[++index])
	{
		arr[SQ] = (arr[SQ] + (!arr[DQ] && str[index] == '\'')) % 2;
		arr[DQ] = (arr[DQ] + (!arr[SQ] && str[index] == '\"')) % 2;
		if (!arr[SQ] && !arr[DQ] && str[index] == '~' && (index == 0 || \
			str[index - 1] != '$'))
		{
			result = ft_substr(str, 0, index);
			path = ft_strjoin(result, tilde);
			free(result);
			result = ft_substr(str, index + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, result);
			free(result);
			free(path);
			return (handle_env_tilde(str, tilde, index + ft_strlen(tilde) - 1));
		}
	}
	free(tilde);
	return (str);
}

char	*toks_extract(t_commands *commands, char *str, int i)
{
	char	*result;
	int		start;
	char	*new_path;
	char	*env;

	start = strchr_mod(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (start == -1)
		start = ft_strlen(str) - 1;
	result = ft_substr(str, 0, i - 1);
	env = get_env_char(&str[i], commands->envp, \
	strchr_mod(&str[i], "\"\'$|>< "));
	if (!env && str[i] == '$')
		env = ft_itoa(commands->pid);
	else if (!env && str[i] == '?')
		env = ft_itoa(g_status);
	new_path = ft_strjoin(result, env);
	free(result);
	result = ft_strjoin(new_path, &str[i + start]);
	free(env);
	free(new_path);
	free(str);
	return (result);
}
