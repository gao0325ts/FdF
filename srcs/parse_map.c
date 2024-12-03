/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:52:28 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 16:44:59 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**parse_map(char *filename, int width, int height)
{
	t_point	**map;
	char	**lines;
	int		i;

	lines = read_map_lines(filename, height);
	if (!lines)
		return (NULL);
	map = (t_point **)malloc(sizeof(t_point *) * height);
	if (!map)
		return (free_split(lines), NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (t_point *)malloc(sizeof(t_point) * width);
		if (!map[i])
		{
			free_split(lines);
			free_map_partial(map, i);
			return (NULL);
		}
		i++;
	}
	set_point(map, lines, width, height);
	free_split(lines);
	return (map);
}

char	**read_map_lines(char *filename, int height)
{
	char	**lines;
	int		fd;
	int		i;

	lines = (char **)malloc(sizeof(char *) * (height + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		free_split(lines);
		return (NULL);
	}
	i = 0;
	while (i <= height)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		i++;
	}
	lines[i] = NULL;
	safe_close_or_exit(fd);
	return (lines);
}

void	set_point(t_point **map, char **lines, int width, int height)
{
	int		i;
	char	**values;

	i = 0;
	while (i < height)
	{
		values = ft_split(lines[i], ' ');
		if (!values)
		{
			free_split(lines);
			free_map_partial(map, height);
			exit(1);
		}
		set_point_process(map[i], values, i, width);
		free_split(values);
		i++;
	}
}

void	set_point_process(t_point *point, char **values, int y, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		point[i].x = i;
		point[i].y = y;
		point[i].z = ft_atoi(values[i]);
		point[i].color = parse_color(values[i]);
		point[i].vx = 0;
		point[i].vy = 0;
		point[i].vz = 0;
		i++;
	}
}

uint32_t	parse_color(char *s)
{
	char		*color_code;
	uint32_t	color;

	while (*s && *s != ',')
		s++;
	if (!*s || !*(s + 1))
		return (0xFFFFFF);
	else
	{
		color_code = s + 1;
		color = hex_to_int(color_code);
	}
	return (color);
}
