/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:19:45 by stakada           #+#    #+#             */
/*   Updated: 2024/11/10 00:22:53 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**contain_words(char **strs, char const *s, char c, int words)
{
	int	i;
	int	len;

	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		strs[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!strs[i])
		{
			while (i--)
				free(strs[i]);
			free(strs);
			return (NULL);
		}
		strs[i][0] = '\0';
		ft_strlcpy(strs[i], s, len + 1);
		s += len;
		i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**strs;

	words = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	strs = contain_words(strs, s, c, words);
	strs[words] = NULL;
	return (strs);
}
