/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:00:05 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/16 17:39:57 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*start;
	char	*end;
	int		len;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = (char *)s1 + ft_strlen(s1) - 1;
	while (end >= start && ft_strchr(set, *end))
		end--;
	len = end - start + 1;
	trimmed = malloc((len + 1) * sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trimmed[i++] = *start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
