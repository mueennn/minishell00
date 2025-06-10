/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:47:38 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/16 17:40:47 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (count);
}

static void	ft_free_split(char **split, size_t i)
{
	while (i > 0)
	{
		free(split[--i]);
	}
	free(split);
}

static char	**ft_split_help(const char *s, char c, char **split)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			split[i++] = ft_substr(s - len, 0, len);
			if (!split[i - 1])
			{
				ft_free_split(split, i);
				return (NULL);
			}
		}
		else
			++s;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = ft_calloc(ft_count(s, c) + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	return (ft_split_help(s, c, split));
}
