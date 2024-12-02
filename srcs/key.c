/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:43:43 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 13:30:09 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation_z(t_vars *env, double angle)
{
	double	center_x;
	double	center_y;
	double	rad_angle;
	double	temp_vx;
	int		i;
	int		j;

	center_x = WIN_WIDTH / 2.0;
	center_y = WIN_HEIGHT / 2.0;
	rad_angle = angle * (M_PI / 180.0);
	i = 0;
	while (i < env->max_height)
	{
		j = 0;
		while (j < env->max_width)
		{
			temp_vx = env->map[i][j].vx;
			env->map[i][j].vx = cos(rad_angle) * (env->map[i][j].vx - center_x)
				- sin(rad_angle) * (env->map[i][j].vy - center_y) + center_x;
			env->map[i][j].vy = sin(rad_angle) * (temp_vx - center_x)
				+ cos(rad_angle) * (env->map[i][j].vy - center_y) + center_y;
			j++;
		}
		i++;
	}
}

void	apply_cabinet(t_vars *env, float angle)
{
	int		i;
	int		j;
	float	rad;

	rad = angle * M_PI / 180.0;
	i = 0;
	while (i < env->max_height)
	{
		j = 0;
		while (j < env->max_width)
		{
			env->map[i][j].vx = env->map[i][j].x + env->map[i][j].z * 0.5
				* cos(rad);
			env->map[i][j].vy = env->map[i][j].y - env->map[i][j].z * 0.5
				* sin(rad);
			j++;
		}
		i++;
	}
}

void	change_projection(t_vars *env)
{
	if (env->cur_projection == 'i')
	{
		apply_cabinet(env, 45.0);
		env->cur_projection = 'p';
	}
	else
	{
		set_v_coordinates_iso(env);
		env->cur_projection = 'i';
	}
	init_position(env->map, env->max_width, env->max_height);
}

void	apply_flatten(t_vars *env, int keycode)
{
	if (keycode == 117)
		env->z_scale += 0.1;
	else
		env->z_scale -= 0.1;
	if (env->z_scale < 0.1)
		env->z_scale = 0.1;
	else if (env->z_scale > 10.0)
		env->z_scale = 10.0;
	set_v_coordinates_iso(env);
	init_position(env->map, env->max_width, env->max_height);
}

int	handle_key(int keycode, t_vars *env)
{
	if (keycode == KEY_Z)
		apply_zoom(env, 1.1);
	else if (keycode == KEY_X)
		apply_zoom(env, 0.9);
	else if (keycode == KEY_A)
		apply_translation(env, -10, 0);
	else if (keycode == KEY_D)
		apply_translation(env, 10, 0);
	else if (keycode == KEY_W)
		apply_translation(env, 0, -10);
	else if (keycode == KEY_S)
		apply_translation(env, 0, 10);
	else if (keycode == KEY_R)
		apply_rotation_z(env, 10);
	else if (keycode == 117 || keycode == 105)
		apply_flatten(env, keycode);
	else if (keycode == SPACE)
		change_projection(env);
	else if (keycode == ESC)
		close_window(env);
	else
		return (0);
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	render(env, env->map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

void	apply_zoom(t_vars *env, double zoom_factor)
{
	double	center_x;
	double	center_y;
	int		i;
	int		j;

	center_x = WIN_WIDTH / 2.0;
	center_y = WIN_HEIGHT / 2.0;
	i = 0;
	while (i < env->max_height)
	{
		j = 0;
		while (j < env->max_width)
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
	while (i < env->max_height)
	{
		j = 0;
		while (j < env->max_width)
		{
			env->map[i][j].vx += offset_x;
			env->map[i][j].vy += offset_y;
			j++;
		}
		i++;
	}
}
