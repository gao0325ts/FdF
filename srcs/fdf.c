/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:47:11 by stakada           #+#    #+#             */
/*   Updated: 2024/11/29 12:35:28 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_zoom(t_vars *env, double zoom_factor)
{
	double	center_x;
	double	center_y;
	int		i;
	int		j;

	center_x = WIN_WIDTH / 2.0;
	center_y = WIN_HEIGHT / 2.0;
	i = 0;
	while (i < env->max_y)
	{
		j = 0;
		while (j < env->max_x)
		{
			env->map[i][j].vx = (env->map[i][j].vx - center_x) * zoom_factor
				+ center_x;
			env->map[i][j].vy = (env->map[i][j].vy - center_y) * zoom_factor
				+ center_y;
			j++;
		}
		i++;
	}
}

void	apply_translation(t_vars *env, double offset_x, double offset_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->max_y)
	{
		j = 0;
		while (j < env->max_x)
		{
			env->map[i][j].vx += offset_x;
			env->map[i][j].vy += offset_y;
			j++;
		}
		i++;
	}
}

int	handle_key(int keycode, t_vars *env)
{
	if (keycode == 122)
		apply_zoom(env, 1.1);
	else if (keycode == 120)
		apply_zoom(env, 0.9);
	else if (keycode == 97)
		apply_translation(env, -10, 0);
	else if (keycode == 100)
		apply_translation(env, 10, 0);
	else if (keycode == 119)
		apply_translation(env, 0, -10);
	else if (keycode == 115)
		apply_translation(env, 0, 10);
	else if (keycode == 65307)
		close_window_esc(env);
	else
		return (0);
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	render(env, env->map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

void	fdf(t_vars *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &(env->bpp), &(env->line_size),
			&(env->endian));
	set_v_coordinates(env->map, env->max_x, env->max_y);
	init_position(env->map, env->max_x, env->max_y);
	render(env, env->map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_hook(env->win, 2, 1L << 0, handle_key, env);
	mlx_hook(env->win, 17, 1L << 5, close_window_x, env);
	mlx_loop(env->mlx);
}

void	init_position(t_point **map, int max_x, int max_y)
{
	t_transform	t;

	t.max_vx = map[0][0].vx;
	t.min_vx = map[0][0].vx;
	t.max_vy = map[0][0].vy;
	t.min_vy = map[0][0].vy;
	find_min_max_vx_vy(map, max_x, max_y, &t);
	t.range_x = t.max_vx - t.min_vx;
	t.range_y = t.max_vy - t.min_vy;
	if (t.range_x == 0 || t.range_y == 0)
		return ;
	t.center_x = (t.max_vx + t.min_vx) / 2.0;
	t.center_y = (t.max_vy + t.min_vy) / 2.0;
	t.zoom_ratio = calculate_zoom_ratio(t.range_x, t.range_y);
	apply_transform(map, max_x, max_y, t);
}

void	render(t_vars *env, t_point **map)
{
	int	i;
	int	j;

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

void	close_window_esc(t_vars *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free_map_partial(env->map, env->max_y);
	free(env->mlx);
	exit(0);
}

int	close_window_x(t_vars *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free_map_partial(env->map, env->max_y);
	free(env->mlx);
	exit(0);
	return (0);
}
