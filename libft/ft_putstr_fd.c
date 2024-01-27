/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinella <grinella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:53:38 by grinella          #+#    #+#             */
/*   Updated: 2023/01/31 11:40:53 by grinella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return	((int)write(fd, s, ft_strlen(s)));
	return 0;
}*/

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}
