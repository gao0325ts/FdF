/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:47:11 by stakada           #+#    #+#             */
/*   Updated: 2024/11/26 18:26:56 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(int keycode, t_vars *env)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_vars *env, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = env->addr + (y * env->line_size + x * (env->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void set_v_coordinates(t_vertex **map, int max_x, int max_y)
{
	int i;
	int j;

	i = 0;
	while (i < max_y)
	{
		j = 0;
		while (j < max_x)
		{
			map[i][j].vx = map[i][j].x * (1.0 / sqrt(2)) + map[i][j].y * (1.0 / sqrt(2));
			map[i][j].vy = -map[i][j].x * (1.0 / sqrt(6)) + map[i][j].y * (1.0 / sqrt(6)) - map[i][j].z * (2.0 / sqrt(6));
			map[i][j].vz = -(map[i][j].x * (1.0 / sqrt(3))) - map[i][j].y * (1.0 / sqrt(3)) + map[i][j].z * (1.0 / sqrt(3));
			j++;
		}
		i++;
	}
}

void draw_line_dda(t_vars *env, t_vertex p1, t_vertex p2)
{
    double dx = p2.vx - p1.vx;
    double dy = p2.vy - p1.vy;
    double x = p1.vx;
    double y = p1.vy;
    double steps;
    int i;

    if (p1.vx == p2.vx && p1.vy == p2.vy)
        return;

    if (fabs(dx) >= fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    
    dx /= steps;
    dy /= steps;

    int start_color = p1.color;
    int end_color = p2.color;

    double r_step = ((end_color >> 16 & 0xFF) - (start_color >> 16 & 0xFF)) / steps;
    double g_step = ((end_color >> 8 & 0xFF) - (start_color >> 8 & 0xFF)) / steps;
    double b_step = ((end_color & 0xFF) - (start_color & 0xFF)) / steps;

    double r = (start_color >> 16) & 0xFF;
    double g = (start_color >> 8) & 0xFF;
    double b = start_color & 0xFF;

    i = 0;
    while (i <= steps)
    {
        int current_color = ((int)r << 16) | ((int)g << 8) | (int)b;
        my_mlx_pixel_put(env, (int)x, (int)y, current_color);
        x += dx;
        y += dy;
        r += r_step;
        g += g_step;
        b += b_step;
        i++;
    }
}

void	render(t_vars *env, t_vertex **map)
{
	int i;
	int j;

	i = 0;
	while (i < env->max_y)
	{
		j = 0;
		while (j < env->max_x)
		{
			my_mlx_pixel_put(env, map[i][j].vx, map[i][j].vy, map[i][j].color);
			if (i + 1 < env->max_y)
				draw_line_dda(env, map[i][j], map[i + 1][j]);
			if (j + 1 < env->max_x)
				draw_line_dda(env, map[i][j], map[i][j + 1]);
			j++;
		}
		i++;
	}
}

void apply_zoom_and_center(t_vertex **map, int max_x, int max_y)
{
    double max_vx = map[0][0].vx;
    double min_vx = map[0][0].vx;
    double max_vy = map[0][0].vy;
    double min_vy = map[0][0].vy;

    for (int i = 0; i < max_y; i++)
    {
        for (int j = 0; j < max_x; j++)
        {
            if (map[i][j].vx > max_vx)
                max_vx = map[i][j].vx;
            if (map[i][j].vx < min_vx)
                min_vx = map[i][j].vx;
            if (map[i][j].vy > max_vy)
                max_vy = map[i][j].vy;
            if (map[i][j].vy < min_vy)
                min_vy = map[i][j].vy;
        }
    }

    double range_x = max_vx - min_vx;
    double range_y = max_vy - min_vy;

    if (range_x == 0 || range_y == 0)
        return;

    double center_x = (max_vx + min_vx) / 2.0;
    double center_y = (max_vy + min_vy) / 2.0;

    double zoom_ratio = 1;
    if (WIN_WIDTH / range_x < WIN_HEIGHT / range_y)
        zoom_ratio = WIN_WIDTH / range_x / 2;
    else
        zoom_ratio = WIN_HEIGHT / range_y / 2;

    for (int i = 0; i < max_y; i++)
    {
        for (int j = 0; j < max_x; j++)
        {
            map[i][j].vx = (map[i][j].vx - center_x) * zoom_ratio + (WIN_WIDTH / 2.0);
            map[i][j].vy = (map[i][j].vy - center_y) * zoom_ratio + (WIN_HEIGHT / 2.0);
        }
    }
}

void	fdf(t_vars *env, t_vertex **map)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &(env->bpp), &(env->line_size),
			&(env->endian));
	set_v_coordinates(map, env->max_x, env->max_y);
	apply_zoom_and_center(map, env->max_x, env->max_y);
	render(env, map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_hook(env->win, 2, 1L << 0, close_window, env);
	mlx_hook(env->win, 17, 1L << 5, mlx_loop_end, env->mlx);
	mlx_loop(env->mlx);
}
