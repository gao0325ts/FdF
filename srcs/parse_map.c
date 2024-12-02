/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:52:28 by stakada           #+#    #+#             */
/*   Updated: 2024/11/29 17:42:32 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**parse_map(char *filename, int max_width, int max_height)
{
	t_point	**map;
	char	**lines;
	int		i;

	lines = read_map_file(filename, max_height);
	map = (t_point **)malloc(sizeof(t_point *) * max_height);
	if (!lines || !map)
		return (NULL);
	i = 0;
	while (i < max_height)
	{
		map[i] = (t_point *)malloc(sizeof(t_point) * max_width);
		if (!map[i])
		{
			free_split(lines);
			free_map_partial(map, i);
			return (NULL);
		}
		set_point_value(map[i], lines[i], i, max_width);
		i++;
	}
	free_split(lines);
	return (map);
}

char	**read_map_file(char *filename, int max_height)
{
	char	**lines;
	int		fd;
	int		i;

	lines = (char **)malloc(sizeof(char *) * (max_height + 1));
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("");
		free_split(lines);
		exit(1);
	}
	i = 0;
	while (i <= max_height)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			break ;
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

void	set_point_value(t_point *point, char *line, int y, int max_width)
{
	char	**strs;
	int		i;

	strs = ft_split(line, ' ');
	i = 0;
	while (i < max_width)
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
		color = hex_string_to_int(color_code);
	}
	return (color);
}

uint32_t	hex_string_to_int(char *s)
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
