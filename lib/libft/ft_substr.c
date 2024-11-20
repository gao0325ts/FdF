/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:23:18 by stakada           #+#    #+#             */
/*   Updated: 2024/11/10 00:23:34 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		return (ft_strdup(&s[start]));
	else
	{
		sub = (char *)malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		while (i < len)
		{
			sub[i] = s[start + i];
			i++;
		}
		sub[i] = '\0';
		return (sub);
	}
}
