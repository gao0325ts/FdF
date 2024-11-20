/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:13:42 by stakada           #+#    #+#             */
/*   Updated: 2024/11/10 00:22:25 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*m;

	i = 0;
	m = (unsigned char *)s;
	while (i < n)
	{
		if (m[i] == (unsigned char)c)
			return ((void *)&(m[i]));
		i++;
	}
	return (NULL);
}
