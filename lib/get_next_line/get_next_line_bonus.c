/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:28:29 by stakada           #+#    #+#             */
/*   Updated: 2024/11/18 03:34:56 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *str)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (!str[len])
		return (ft_strdup(str));
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*save_ramaining_str(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || (str[i] == '\n' && !str[i + 1]))
	{
		free(str);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!new)
		return (NULL);
	j = 0;
	while (str[i + 1])
	{
		new[j] = str[i + 1];
		i++;
		j++;
	}
	new[j] = '\0';
	free(str);
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

static t_list	*get_fd_node(t_list **lst, int fd)
{
	t_list	*new;
	t_list	*current;

	current = *lst;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->store = NULL;
	new->next = *lst;
	*lst = new;
	return (new);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_list			*current;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_fd_node(&lst, fd);
	if (!current)
		return (NULL);
	current->store = read_and_append(fd, current->store);
	if (!current->store)
	{
		free_current_fd(&lst, fd);
		return (NULL);
	}
	line = extract_line(current->store);
	current->store = save_ramaining_str(current->store);
	return (line);
}
