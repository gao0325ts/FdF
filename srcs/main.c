/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:06:22 by stakada           #+#    #+#             */
/*   Updated: 2024/11/26 19:52:25 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int ac, char **av)
{
	t_vars	env;
	t_vertex	**map;

	if (ac != 2)
	{
		perror("Invalid argument");
		return (1);
	}
	check_map(av[1], &env.max_x, &env.max_y);
	map = parse_map(av[1], env.max_x, env.max_y);
	if (!map)
		return (1);
	fdf(&env, map);
	return (0);
}
