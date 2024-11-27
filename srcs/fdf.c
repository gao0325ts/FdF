/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:47:11 by stakada           #+#    #+#             */
/*   Updated: 2024/11/27 17:16:57 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(int keycode, t_vars *env)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		// TODO destroy display
		exit(0);
	}
	return (0);
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

void	apply_zoom_and_center(t_point **map, int max_x, int max_y)
{
	double		min_max[4];
	t_transform	t;

	min_max[0] = map[0][0].vx;
	min_max[1] = map[0][0].vx;
	min_max[2] = map[0][0].vy;
	min_max[3] = map[0][0].vy;
	find_min_max_vx_vy(map, max_x, max_y, min_max);
	t.range_x = min_max[0] - min_max[1];
	t.range_y = min_max[2] - min_max[3];
	if (t.range_x == 0 || t.range_y == 0)
		return ;
	t.center_x = (min_max[0] + min_max[1]) / 2.0;
	t.center_y = (min_max[2] + min_max[3]) / 2.0;
	t.zoom_ratio = calculate_zoom_ratio(t.range_x, t.range_y);
	apply_transform(map, max_x, max_y, t);
}

void	fdf(t_vars *env, t_point **map)
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
