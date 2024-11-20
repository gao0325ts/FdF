/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:09:22 by stakada           #+#    #+#             */
/*   Updated: 2024/11/10 00:22:23 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long num)
{
	int	digits;

	digits = 1;
	if (num < 0)
	{
		digits++;
		num = -num;
	}
	while (num >= 10)
	{
		num /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		sign;
	int		digits;

	num = (long)n;
	sign = 0;
	if (num < 0)
		sign = 1;
	digits = count_digits(num);
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	str[digits] = '\0';
	if (sign)
	{
		str[0] = '-';
		num = -num;
	}
	while (digits-- > sign)
	{
		str[digits] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
