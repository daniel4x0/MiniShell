/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engirald <engirald@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:38:17 by engirald          #+#    #+#             */
/*   Updated: 2024/01/27 18:38:14 by engirald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
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
