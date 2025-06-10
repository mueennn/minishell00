/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:59:54 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/15 11:59:55 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;
	int	equal_pos;

	if (!str || !*str)
		return (0);
	equal_pos = 0;
	while (str[equal_pos] && str[equal_pos] != '=')
		equal_pos++;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (i < equal_pos && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
