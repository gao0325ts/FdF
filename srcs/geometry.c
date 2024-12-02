/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:21:20 by stakada           #+#    #+#             */
/*   Updated: 2024/11/29 23:11:35 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_v_coordinates_iso(t_vars *env)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->max_height)
	{
		j = 0;
		while (j < env->max_width)
		{
			env->map[i][j].vx = env->map[i][j].x * (1.0 / sqrt(2))
				+ env->map[i][j].y * (1.0 / sqrt(2));
			env->map[i][j].vy = -env->map[i][j].x * (1.0 / sqrt(6))
				+ env->map[i][j].y * (1.0 / sqrt(6)) - env->map[i][j].z
				* env->z_scale * (2.0 / sqrt(6));
			env->map[i][j].vz = -(env->map[i][j].x * (1.0 / sqrt(3)))
				- env->map[i][j].y * (1.0 / sqrt(3)) + env->map[i][j].z
				* env->z_scale * (1.0 / sqrt(3));
			j++;
		}
		i++;
	}
}

void	find_min_max_vx_vy(t_point **map, int max_width, int max_height,
		t_transform *t)
{
	int	i;
	int	j;

	i = 0;
	while (i < max_height)
	{
		j = 0;
		while (j < max_width)
		{
			if (map[i][j].vx > t->max_vx)
				t->max_vx = map[i][j].vx;
			if (map[i][j].vx < t->min_vx)
				t->min_vx = map[i][j].vx;
			if (map[i][j].vy > t->max_vy)
				t->max_vy = map[i][j].vy;
			if (map[i][j].vy < t->min_vy)
				t->min_vy = map[i][j].vy;
			j++;
		}
		i++;
	}
}

double	calculate_zoom_ratio(double range_x, double range_y)
{
	double	ratio;

	ratio = 1;
	if (WIN_WIDTH / range_x < WIN_HEIGHT / range_y)
		ratio = WIN_WIDTH / range_x / 1.1;
	else
		ratio = WIN_HEIGHT / range_y / 1.1;
	return (ratio);
}

void	apply_transform(t_point **map, int max_width, int max_height,
		t_transform t)
{
	int	i;
	int	j;

	i = 0;
	while (i < max_height)
	{
		j = 0;
		while (j < max_width)
		{
			map[i][j].vx = (map[i][j].vx - t.center_x) * t.zoom_ratio
				+ (WIN_WIDTH / 2.0);
			map[i][j].vy = (map[i][j].vy - t.center_y) * t.zoom_ratio
				+ (WIN_HEIGHT / 2.0);
			j++;
		}
		i++;
	}
}
