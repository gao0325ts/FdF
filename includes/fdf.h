/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:07:05 by stakada           #+#    #+#             */
/*   Updated: 2024/11/22 21:47:04 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_size;
	int			endian;
	int			max_x;
	int			max_y;
}				t_vars;

typedef struct s_vertex
{
	double		x;
	double		y;
	double		z;
	double		vx;
	double		vy;
	double		vz;
	uint32_t	color;
}				t_vertex;

// check_map.c
void	check_map(char *filename, int *max_x, int *max_y);
void	get_max_value(int fd, int *max_x, int *max_y);
void	get_max_x(char *line, int *max_x, int is_first_line);

// parse_map.c
t_vertex		**parse_map(char *filename, int max_x, int max_y);
void	set_vertex_value(t_vertex *point, char *line, int y, int max_x);
uint32_t	parse_color(char *s);
uint32_t	char_to_digit(char c);
uint32_t	hex_string_to_int(char *s);

// free.c
void	free_split(char **strs);

// str_to_double.c
double	str_to_double(char *str);
void	str_to_double_components(char *s, double *res, double *frac);

// fdf.c
void	fdf(t_vars *env, t_vertex **map);
int	close_window(int keycode, t_vars *env);
void	my_mlx_pixel_put(t_vars *env, int x, int y, int color);

#endif