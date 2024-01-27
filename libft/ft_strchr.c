/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:06:48 by grinella          #+#    #+#             */
/*   Updated: 2023/02/02 12:28:24 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)&s[i]);
	return (0);
}

int	ft_strchr_i(const char *str, int c)
{
	unsigned char	cc;
	int				i;

	i = 0;
	if (!str)
		return (-1);
	cc = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
			return (i);
		i++;
	}
	if (cc == '\0')
		return (i);
	return (-1);
}

int	strchr_mod(const char *s, char *set)
{
	int				i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]))
			return (i);
		i++;
	}
	return (-1);
}
