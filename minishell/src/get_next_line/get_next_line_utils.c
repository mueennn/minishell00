/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:49:38 by arimoham          #+#    #+#             */
/*   Updated: 2025/04/11 15:14:05 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*ft_gnl_strjoin(char const *str1, char const *str2)
{
	int		len;
	int		i;
	int		j;
	char	*joined;

	if (!str1 && !str2)
		return (NULL);
	len = ft_gnl_strlen(str1) + ft_gnl_strlen(str2);
	joined = malloc(sizeof(char) * (len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	if (str1)
		while (str1[i])
			joined[j++] = str1[i++];
	i = 0;
	if (str2)
		while (str2[i])
			joined[j++] = str2[i++];
	joined[j] = '\0';
	return (joined);
}

size_t	ft_gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_gnl_strchr(const char *str, int character)
{
	if (!str)
		return (0);
	while (*str != character)
	{
		if (!*str)
			return (0);
		str++;
	}
	return ((char *)str);
}

char	*ft_gnl_strdup(const char *str1)
{
	size_t	i;
	char	*str2;

	str2 = malloc(sizeof(char *) * (ft_gnl_strlen(str1) + 1));
	if (!str2)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
