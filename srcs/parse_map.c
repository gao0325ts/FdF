/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:52:28 by stakada           #+#    #+#             */
/*   Updated: 2024/11/27 16:04:07 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**parse_map(char *filename, int max_x, int max_y)
{
	t_point	**map;
	int		fd;
	char	*line;
	int		i;

	map = (t_point **)malloc(sizeof(t_point *) * max_y);
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < max_y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[i] = (t_point *)malloc(sizeof(t_point) * max_x);
		if (!map[i])
			return (NULL);
		set_point_value(map[i], line, i, max_x);
		free(line);
		i++;
	}
	close(fd);
	return (map);
}

void	set_point_value(t_point *point, char *line, int y, int max_x)
{
	char	**strs;
	int		i;

	strs = ft_split(line, ' ');
	i = 0;
	while (i < max_x)
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

uint32_t	char_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
	{
		perror("Invalid color");
		exit(1);
	}
}

uint32_t	hex_string_to_int(char *s)
{
	uint32_t	result;

	result = 0;
	if (s[0] == '0' && s[1] == 'x')
		s += 2;
	while (*s && *s != '\n')
	{
		result = (result << 4) | char_to_digit(*s);
		s++;
	}
	return (result);
}
