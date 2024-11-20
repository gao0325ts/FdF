/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:35:24 by stakada           #+#    #+#             */
/*   Updated: 2024/11/10 00:22:31 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_copy;
	const unsigned char	*src_copy;

	dest_copy = (unsigned char *)dest;
	src_copy = (unsigned char *)src;
	while (n--)
		*dest_copy++ = *src_copy++;
	return (dest);
}
