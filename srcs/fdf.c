/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:47:11 by stakada           #+#    #+#             */
/*   Updated: 2024/11/29 11:24:55 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf(t_vars *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &(env->bpp), &(env->line_size),
			&(env->endian));
	set_v_coordinates(env->map, env->max_x, env->max_y);
	apply_zoom_and_center(env->map, env->max_x, env->max_y);
	render(env, env->map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	hook(env);
	mlx_loop(env->mlx);
}

void	hook(t_vars *env)
{
	mlx_hook(env->win, 2, 1L << 0, close_window_esc, env);
	mlx_hook(env->win, 17, 1L << 5, close_window_x, env);
}

void	apply_zoom_and_center(t_point **map, int max_x, int max_y)
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

int	close_window_esc(int keycode, t_vars *env)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy_display(env->mlx);
		free_map_partial(env->map, env->max_y);
		free(env->mlx);
		exit(0);
	}
	return (0);
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
