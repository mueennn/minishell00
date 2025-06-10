/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:29:19 by rradin-m          #+#    #+#             */
/*   Updated: 2024/07/10 14:04:41 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		count;
	long	num;

	count = count_digits(n);
	num = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	result = malloc(count + 1);
	if (!result)
		return (NULL);
	result[count] = '\0';
	if (num < 0)
		num = -num;
	while (count-- > 0)
	{
		result[count] = '0' + (num % 10);
		num /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
