/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:06:22 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 15:38:44 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_vars	env;

	if (ac != 2)
	{
		ft_putendl_fd("Error: Invalid argument", STDERR_FILENO);
		return (1);
	}
	check_map(av[1], &env.width, &env.height);
	env.map = parse_map(av[1], env.width, env.height);
	if (!env.map)
	{
		ft_putendl_fd("Error: Failed to parse map", STDERR_FILENO);
		return (1);
	}
	fdf(&env);
	return (0);
}
