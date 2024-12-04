/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:46:54 by stakada           #+#    #+#             */
/*   Updated: 2024/12/04 21:47:16 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	process_key_input(int keycode, t_vars *env)
{
	handle_key_action(keycode, env);
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	render_map(env, env->map, env->width, env->height);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

void	handle_key_action(int keycode, t_vars *env)
{
	if (keycode == KEY_Z)
		zoom_map(env, 1.1);
	else if (keycode == KEY_X)
		zoom_map(env, 0.9);
	else if (keycode == KEY_A)
		translate_map(env, -10, 0);
	else if (keycode == KEY_D)
		translate_map(env, 10, 0);
	else if (keycode == KEY_W)
		translate_map(env, 0, -10);
	else if (keycode == KEY_S)
		translate_map(env, 0, 10);
	else if (keycode == KEY_R)
		rotate_z_axis(env, 10);
	else if (keycode == KEY_I || keycode == KEY_U)
		adjust_map_flatness(env, keycode);
	else if (keycode == SPACE)
		toggle_projection(env);
	else if (keycode == ESC)
		close_window(env);
}
