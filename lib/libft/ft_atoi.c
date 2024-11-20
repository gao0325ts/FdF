/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:02:59 by stakada           #+#    #+#             */
/*   Updated: 2024/11/12 01:29:33 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		if (sign == 1 && result > (INT_MAX - (*nptr - '0')) / 10)
			return ((int)LONG_MAX);
		else if (sign == -1 && -(result) < (INT_MIN + (*nptr - '0')) / 10)
			return ((int)LONG_MIN);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}
