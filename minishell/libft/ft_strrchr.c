/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:22:21 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/17 15:02:32 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			temp = (char *)s + i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (temp);
}
