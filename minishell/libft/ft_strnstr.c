/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:32:17 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/16 17:40:03 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*ps;
	const char	*pn;
	size_t		needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack && len >= needle_len)
	{
		ps = haystack;
		pn = needle;
		while (*ps && *pn && (*ps == *pn))
		{
			ps++;
			pn++;
		}
		if (*pn == '\0')
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
