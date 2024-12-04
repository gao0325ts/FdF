/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:02:28 by stakada           #+#    #+#             */
/*   Updated: 2024/12/04 16:56:50 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_map(char *filename, int *width, int *height)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		exit(1);
	}
	*width = 0;
	*height = 0;
	if (get_map_size(fd, width, height) == -1)
	{
		safe_close_or_exit(fd);
		exit(1);
	}
	safe_close_or_exit(fd);
}

int	get_map_size(int fd, int *width, int *height)
{
	char	*line;
	int		is_first_line;

	is_first_line = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*height)++;
		if (get_map_width(line, width, is_first_line) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
		is_first_line = 0;
	}
	if (is_first_line)
	{
		ft_putendl_fd("Error: File is empty", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	get_map_width(char *line, int *width, int is_first_line)
{
	char	**strs;
	int		i;

	strs = ft_split(line, ' ');
	if (!strs)
		return (-1);
	i = 0;
	while (strs[i] && strs[i][0] != '\n')
		i++;
	if (i == 0 || (!is_first_line && *width != i))
	{
		ft_putendl_fd("Error: Map width mismatch", STDERR_FILENO);
		free_split(strs);
		return (-1);
	}
	*width = i;
	free_split(strs);
	return (0);
}
