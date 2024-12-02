/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:52:28 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 15:02:07 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**parse_map(char *filename, int width, int height)
{
	t_point	**map;
	char	**lines;
	int		i;

	lines = read_map_file(filename, height);
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
		// set_point(map[i], lines[i], i, width);
		i++;
	}
	set_point(map, lines, width, height);
	free_split(lines);
	return (map);
}

char	**read_map_file(char *filename, int height)
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
		exit(1);
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

// void set_point(t_point **map, char **lines, int width, int height)

int	set_point(t_point *point, char *line, int width)
{
	char	**strs;
	int		i;

	strs = ft_split(line, ' ');
	if (!strs)
	{
		ft_putendl_fd("Error: Memory allocation failed in ft_split", STDERR_FILENO);
		return (-1);
	}
	i = 0;
	while (i < width)
	{
		point[i].x = i;
		point[i].y = y;
		point[i].z = ft_atoi(strs[i]);
		point[i].color = parse_color(strs[i]);
		point[i].vx = 0;
		point[i].vy = 0;
		point[i].vz = 0;
		i++;
	}
	free_split(strs);
	return (0);
}

uint32_t	parse_color(char *s)
{
	char		*color_code;
	uint32_t	color;

	while (*s && *s != ',')
		s++;
	if (!*s)
		return (0xFFFFFF);
	else
	{
		color_code = s + 1;
		color = hex_to_int(color_code);
	}
	return (color);
}

uint32_t	hex_to_int(char *s)
{
	uint32_t	result;
	uint32_t	digit;

	result = 0;
	if (s[0] == '0' && s[1] == 'x')
		s += 2;
	while (*s && *s != '\n')
	{
		if (*s >= '0' && *s <= '9')
			digit = *s - '0';
		else if (*s >= 'a' && *s <= 'f')
			digit = *s - 'a' + 10;
		else if (*s >= 'A' && *s <= 'F')
			digit = *s - 'A' + 10;
		result = (result << 4) | digit;
		s++;
	}
	return (result);
}
