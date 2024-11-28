/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:06:22 by stakada           #+#    #+#             */
/*   Updated: 2024/11/28 22:40:53 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_vars	env;

	if (ac != 2)
	{
		write(2, "Invalid argument\n", 18);
		return (1);
	}
	check_map(av[1], &env.max_x, &env.max_y);
	env.map = parse_map(av[1], env.max_x, env.max_y);
	if (!env.map)
	{
		write(2, "Failed to parse map\n", 21);
		return (1);
	}
	fdf(&env);
	return (0);
}
