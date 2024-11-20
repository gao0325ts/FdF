/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:21:58 by stakada           #+#    #+#             */
/*   Updated: 2024/11/18 02:39:00 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *s)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (!s[len])
		return (ft_strdup(s));
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*save_ramaining_str(char *s)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i] || (s[i] == '\n' && !s[i + 1]))
	{
		free(s);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(s) - i));
	if (!new)
		return (NULL);
	j = 0;
	while (s[i + 1])
	{
		new[j] = s[i + 1];
		i++;
		j++;
	}
	new[j] = '\0';
	free(s);
	return (new);
}

static char	*read_and_append(int fd, char *store)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			free(store);
			return (NULL);
		}
		buf[bytes] = '\0';
		if (bytes == 0)
			break ;
		store = join_string(store, buf);
		if (!store || ft_strchr(store, '\n'))
			break ;
	}
	free(buf);
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_and_append(fd, store);
	if (!store)
		return (NULL);
	line = extract_line(store);
	store = save_ramaining_str(store);
	return (line);
}
