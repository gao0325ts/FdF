/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:07:05 by stakada           #+#    #+#             */
/*   Updated: 2024/11/29 11:26:19 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 1024
# define WIN_HEIGHT 1024

# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	double		vx;
	double		vy;
	double		vz;
	uint32_t	color;
}				t_point;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_point		**map;
	int			max_x;
	int			max_y;
}				t_vars;

typedef struct s_transform
{
	double		max_vx;
	double		min_vx;
	double		max_vy;
	double		min_vy;
	double		range_x;
	double		range_y;
	double		center_x;
	double		center_y;
	double		zoom_ratio;
}				t_transform;

typedef struct s_color
{
	double		r;
	double		g;
	double		b;
	double		r_step;
	double		g_step;
	double		b_step;
}				t_color;

typedef struct s_line
{
	double		dx;
	double		dy;
	double		x;
	double		y;
}				t_line;

// check_map.c
void			check_map(char *filename, int *max_x, int *max_y);
int				get_max_value(int fd, int *max_x, int *max_y);
int				get_max_x(char *line, int *max_x, int is_first_line);

// parse_map.c
t_point			**parse_map(char *filename, int max_x, int max_y);
char			**read_map_file(char *filename, int max_y);
void			set_point_value(t_point *point, char *line, int y, int max_x);
uint32_t		parse_color(char *s);
uint32_t		hex_string_to_int(char *s);

// free.c
void			free_split(char **strs);
void			free_map_partial(t_point **map, int index);

// fdf.c
void			fdf(t_vars *env);
void			hook(t_vars *env);
int				close_window_esc(int keycode, t_vars *env);
int				close_window_x(t_vars *env);
void			render(t_vars *env, t_point **map);
void			apply_zoom_and_center(t_point **map, int max_x, int max_y);

// drawing.c
void			my_mlx_pixel_put(t_vars *env, int x, int y, int color);
void			calculate_color(t_color *color, int start, int end,
					double steps);
void			update_line_and_color(t_line *line, t_color *color);
void			draw_line_dda(t_vars *env, t_point p1, t_point p2);

// geometry.c
void			set_v_coordinates(t_point **map, int max_x, int max_y);
void			find_min_max_vx_vy(t_point **map, int max_x, int max_y,
					t_transform *t);
double			calculate_zoom_ratio(double range_x, double range_y);
void			apply_transform(t_point **map, int max_x, int max_y,
					t_transform t);

#endif