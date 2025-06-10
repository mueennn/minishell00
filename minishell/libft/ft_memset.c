/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:51:12 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/16 18:27:16 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*str_ptr;

	str_ptr = (unsigned char *)str;
	while (n--)
		*str_ptr++ = (unsigned char)c;
	return (str);
}
