/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:02:28 by stakada           #+#    #+#             */
/*   Updated: 2024/11/28 22:59:40 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_map(char *filename, int *max_x, int *max_y)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("");
		exit(1);
	}
	*max_x = 0;
	*max_y = 0;
	if (get_max_value(fd, max_x, max_y) < 0)
	{
		close(fd);
		exit(1);
	}
	close(fd);
}

int	get_max_value(int fd, int *max_x, int *max_y)
{
	char	*line;
	int		is_first_line;

	is_first_line = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*max_y)++;
		if (get_max_x(line, max_x, is_first_line) < 0)
		{
			write(2, "Invalid map format\n", 20);
			free(line);
			return (-1);
		}
		free(line);
		is_first_line = 0;
	}
	if (is_first_line)
	{
		write(2, "Empty file\n", 12);
		return (-1);
	}
	return (0);
}

int	get_max_x(char *line, int *max_x, int is_first_line)
{
	char	**strs;
	int		i;

	strs = ft_split(line, ' ');
	i = 0;
	while (strs[i] && strs[i][0] != '\n')
		i++;
	if (i == 0 || (!is_first_line && *max_x != i))
	{
		free_split(strs);
		return (-1);
	}
	*max_x = i;
	free_split(strs);
	return (0);
}
