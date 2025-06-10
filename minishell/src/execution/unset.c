/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:40:40 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/21 16:33:59 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unset_var(char **envp, char *var_name)
{
	int		i;
	char	*equal_sign;
	size_t	name_len;

	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - envp[i];
			if (name_len == ft_strlen(var_name) && !ft_strncmp(envp[i],
					var_name, name_len))
			{
				ft_array_replace_in(&envp, NULL, i);
				break ;
			}
		}
		i++;
	}
}

int	mini_unset(t_prompt *prompt)
{
	char	**argv;
	int		i;
	int		ij[2];

	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_arraylen(argv) < 2)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (var_in_envp(argv[i], prompt->envp, ij))
			ft_array_replace_in(&prompt->envp, NULL, ij[1]);
		else
			unset_var(prompt->envp, argv[i]);
		i++;
	}
	return (0);
}
