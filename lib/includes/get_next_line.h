/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:22:06 by stakada           #+#    #+#             */
/*   Updated: 2024/11/15 16:19:48 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*join_string(char *s1, char *s2);
char	*ft_strdup(char *s);
size_t	ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);

#endif