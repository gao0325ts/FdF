/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:47:11 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 16:30:18 by stakada          ###   ########.fr       */
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
	env->z_scale = 1.0;
	convert_to_iso_coord(env);
	init_map_position(env->map, env->width, env->height);
	render_map(env, env->map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_hook(env->win, 2, 1L << 0, process_key_input, env);
	mlx_hook(env->win, 17, 1L << 5, close_window, env);
	mlx_loop(env->mlx);
}

void	init_map_position(t_point **map, int width, int height)
{
	t_transform	t;

	t.max_vx = map[0][0].vx;
	t.min_vx = map[0][0].vx;
	t.max_vy = map[0][0].vy;
	t.min_vy = map[0][0].vy;
	find_bounds(map, width, height, &t);
	t.range_x = t.max_vx - t.min_vx;
	t.range_y = t.max_vy - t.min_vy;
	if (t.range_x == 0 || t.range_y == 0)
		return ;
	t.center_x = (t.max_vx + t.min_vx) / 2.0;
	t.center_y = (t.max_vy + t.min_vy) / 2.0;
	t.zoom_ratio = calculate_zoom_ratio(t.range_x, t.range_y);
	apply_transform(map, width, height, t);
}

void	render_map(t_vars *env, t_point **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			my_mlx_pixel_put(env, map[i][j].vx, map[i][j].vy, map[i][j].color);
			if (i + 1 < env->height)
				draw_line_dda(env, map[i][j], map[i + 1][j]);
			if (j + 1 < env->width)
				draw_line_dda(env, map[i][j], map[i][j + 1]);
			j++;
		}
		i++;
	}
}

int	close_window(t_vars *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	mlx_destroy_display(env->mlx);
	free_map_partial(env->map, env->height);
	free(env->mlx);
	exit(0);
	return (0);
}
