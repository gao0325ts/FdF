/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:05:52 by stakada           #+#    #+#             */
/*   Updated: 2024/11/22 19:06:00 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	str_to_double(char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0.0;
	fraction = 0.0;
	sign = 1;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	str_to_double_components(str, &result, &fraction);
	return (sign * (result + fraction));
}

void	str_to_double_components(char *s, double *res, double *frac)
{
	int		is_fraction;
	double	divisor;

	is_fraction = 0;
	divisor = 1.0;
	while (*s)
	{
		if (ft_isdigit(*s))
		{
			if (is_fraction)
			{
				divisor *= 10.0;
				*frac += (*s - '0') / divisor;
			}
			else
				*res = *res * 10.0 + (*s - '0');
		}
		else if (*s == '.' && !is_fraction)
			is_fraction = 1;
		else
			break ;
		s++;
	}
}
