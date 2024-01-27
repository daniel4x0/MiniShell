/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duzegbu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:36:59 by duzegbu           #+#    #+#             */
/*   Updated: 2023/03/15 17:37:04 by duzegbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include "../libft/libft.h"

char	*get_next_line(int fd);
char	*ft_read_to_left_str(int fd, char *left_str);
//char	*ft_strchr(const char *s, int c);
//char	*ft_strjoin(char const *s1, char const *s2);
//size_t	ft_strlen(const char *str);
char	*ft_get_line(char *left_str);
char	*ft_new_left_str(char *left_str);

#endif
