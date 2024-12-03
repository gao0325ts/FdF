/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:07:05 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 16:49:29 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIN_WIDTH 1980
# define WIN_HEIGHT 1080
# define ESC 65307
# define SPACE 32
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define ALLOW_UP 65362
# define ALLOW_DOWN 65364
# define ALLOW_LEFT 65361
# define ALLOW_RIGHT 65363
# define KEY_Z 122
# define KEY_X 120
# define KEY_R 114
# define PLUS 65505
# define MINUS 45

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
	int			width;
	int			height;
	char		cur_projection;
	double		z_scale;
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
void			check_map(char *filename, int *width, int *height);
int				get_max_value(int fd, int *width, int *height);
int				get_width(char *line, int *width, int is_first_line);

// parse_map.c
t_point			**parse_map(char *filename, int width, int height);
char			**read_map_lines(char *filename, int height);
void			set_point(t_point **map, char **lines, int width, int height);
void			set_point_process(t_point *point, char **values, int y,
					int width);
uint32_t		parse_color(char *s);

// free.c
void			free_split(char **strs);
void			free_map_partial(t_point **map, int index);

// fdf.c
void			fdf(t_vars *env);
void			init_map_position(t_point **map, int width, int height);
void			render_map(t_vars *env, t_point **map);
int				close_window(t_vars *env);

// draw.c
void			my_mlx_pixel_put(t_vars *env, int x, int y, int color);
void			calculate_color(t_color *color, int start, int end,
					double steps);
void			update_line_and_color(t_line *line, t_color *color);
void			draw_line_dda(t_vars *env, t_point p1, t_point p2);

// geometry.c
void			convert_to_iso_coord(t_vars *env);
void			find_bounds(t_point **map, int width, int height,
					t_transform *t);
double			calculate_zoom_ratio(double range_x, double range_y);
void			apply_transform(t_point **map, int width, int height,
					t_transform t);

// operations.c
void			rotate_z_axis(t_vars *env, double angle);
void			apply_parallel_projection(t_vars *env, float angle);
void			toggle_projection(t_vars *env);
void			adjust_map_flatness(t_vars *env, int keycode);
void			update_z_influence(t_vars *env);
void			translate_map(t_vars *env, double offset_x, double offset_y);
void			zoom_map(t_vars *env, double zoom_factor);

// 

// utils.c
void			safe_close_or_exit(int fd);
uint32_t		hex_to_int(char *s);

// key.c
int				process_key_input(int keycode, t_vars *env);
void			handle_key_action(int keycode, t_vars *env);

#endif