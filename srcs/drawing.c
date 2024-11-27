/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:21:01 by stakada           #+#    #+#             */
/*   Updated: 2024/11/27 17:09:22 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_vars *env, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = env->addr + (y * env->line_size + x * (env->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	calculate_color(t_color *color, int start, int end, double steps)
{
	color->r_step = ((end >> 16 & 0xFF) - (start >> 16 & 0xFF)) / steps;
	color->g_step = ((end >> 8 & 0xFF) - (start >> 8 & 0xFF)) / steps;
	color->b_step = ((end & 0xFF) - (start & 0xFF)) / steps;
	color->r = (start >> 16) & 0xFF;
	color->g = (start >> 8) & 0xFF;
	color->b = start & 0xFF;
}

void	update_line_and_color(t_line *line, t_color *color)
{
	line->x += line->dx;
	line->y += line->dy;
	color->r += color->r_step;
	color->g += color->g_step;
	color->b += color->b_step;
}

void	draw_line_dda(t_vars *env, t_point p1, t_point p2)
{
	t_line	line;
	t_color	color;
	double	steps;

	if (p1.vx == p2.vx && p1.vy == p2.vy)
		return ;
	line.dx = p2.vx - p1.vx;
	line.dy = p2.vy - p1.vy;
	line.x = p1.vx;
	line.y = p1.vy;
	if (fabs(line.dx) >= fabs(line.dy))
		steps = fabs(line.dx);
	else
		steps = fabs(line.dy);
	line.dx /= steps;
	line.dy /= steps;
	calculate_color(&color, p1.color, p2.color, steps);
	while (steps >= 0)
	{
		my_mlx_pixel_put(env, (int)line.x, (int)line.y,
			(((int)color.r << 16) | ((int)color.g << 8) | (int)color.b));
		update_line_and_color(&line, &color);
		steps--;
	}
}
