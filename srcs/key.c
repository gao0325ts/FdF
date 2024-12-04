/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:46:54 by stakada           #+#    #+#             */
/*   Updated: 2024/12/04 22:16:34 by stakada          ###   ########.fr       */
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
	if (keycode == XK_plus)
		zoom_map(env, 1.1);
	else if (keycode == XK_minus)
		zoom_map(env, 0.9);
	else if (keycode == XK_Left)
		translate_map(env, -10, 0);
	else if (keycode == XK_Right)
		translate_map(env, 10, 0);
	else if (keycode == XK_Up)
		translate_map(env, 0, -10);
	else if (keycode == XK_Down)
		translate_map(env, 0, 10);
	else if (keycode == XK_d)
		rotate_z_axis(env, 10);
	else if (keycode == XK_a)
		rotate_z_axis(env, -10);
	else if (keycode == XK_w || keycode == XK_s)
		adjust_map_flatness(env, keycode);
	else if (keycode == XK_space)
		toggle_projection(env);
	else if (keycode == XK_Escape)
		close_window(env);
}
