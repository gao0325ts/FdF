/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:42:08 by stakada           #+#    #+#             */
/*   Updated: 2024/12/02 15:29:17 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	safe_close_or_exit(int fd)
{
	if (close(fd) == -1)
	{
		perror("Error");
		exit(1);
	}
}

uint32_t	hex_to_int(char *s)
{
	uint32_t	result;
	uint32_t	digit;

	result = 0;
	if (s[0] == '0' && s[1] == 'x')
		s += 2;
	while (*s && *s != '\n')
	{
		if (*s >= '0' && *s <= '9')
			digit = *s - '0';
		else if (*s >= 'a' && *s <= 'f')
			digit = *s - 'a' + 10;
		else if (*s >= 'A' && *s <= 'F')
			digit = *s - 'A' + 10;
		result = (result << 4) | digit;
		s++;
	}
	return (result);
}
