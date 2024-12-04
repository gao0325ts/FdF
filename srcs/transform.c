/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:43:52 by stakada           #+#    #+#             */
/*   Updated: 2024/12/04 22:32:09 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	toggle_projection(t_vars *env)
{
	if (env->cur_projection == 'i')
	{
		convert_to_parallel_coord(env, P_ANGLE);
		env->cur_projection = 'p';
	}
	else
	{
		convert_to_iso_coord(env);
		env->cur_projection = 'i';
	}
	init_map_position(env->map, env->width, env->height);
}

void	convert_to_parallel_coord(t_vars *env, double angle)
{
	int		i;
	int		j;

	angle = angle * (M_PI / 180.0);
	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			env->map[i][j].vx = env->map[i][j].x + env->map[i][j].z * 0.5
				* cos(angle);
			env->map[i][j].vy = env->map[i][j].y - env->map[i][j].z * 0.5
				* sin(angle);
			j++;
		}
		i++;
	}
}

void	adjust_map_flatness(t_vars *env, int keycode)
{
	if (keycode == XK_w)
		env->z_scale += 0.1;
	else
		env->z_scale -= 0.1;
	if (env->z_scale < 0.1)
		env->z_scale = 0.1;
	else if (env->z_scale > 5.0)
		env->z_scale = 5.0;
	convert_to_iso_coord(env);
	init_map_position(env->map, env->width, env->height);
}
