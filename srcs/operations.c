/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:43:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/04 21:43:57 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_map(t_vars *env, double offset_x, double offset_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			env->map[i][j].vx += offset_x;
			env->map[i][j].vy += offset_y;
			j++;
		}
		i++;
	}
}

void	zoom_map(t_vars *env, double zoom_factor)
{
	double	center_x;
	double	center_y;
	int		i;
	int		j;

	center_x = WIN_WIDTH / 2.0;
	center_y = WIN_HEIGHT / 2.0;
	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
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

void	rotate_z_axis(t_vars *env, double angle)
{
	double	center_x;
	double	center_y;
	double	temp_vx;
	int		i;
	int		j;

	center_x = WIN_WIDTH / 2.0;
	center_y = WIN_HEIGHT / 2.0;
	angle = angle * (M_PI / 180.0);
	i = 0;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			temp_vx = env->map[i][j].vx;
			env->map[i][j].vx = cos(angle) * (env->map[i][j].vx - center_x)
				- sin(angle) * (env->map[i][j].vy - center_y) + center_x;
			env->map[i][j].vy = sin(angle) * (temp_vx - center_x)
				+ cos(angle) * (env->map[i][j].vy - center_y) + center_y;
			j++;
		}
		i++;
	}
}
