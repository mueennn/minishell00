/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:31:13 by arimoham          #+#    #+#             */
/*   Updated: 2025/04/21 16:37:44 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

static int	check_env_match(char *argv, char *env_var, int var_len)
{
	char	*equal_sign;
	int		env_name_len;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		env_name_len = equal_sign - env_var;
		if (var_len == env_name_len && !ft_strncmp(env_var, argv, var_len))
			return (1);
	}
	else if (!ft_strncmp(env_var, argv, var_len))
		return (1);
	return (0);
}

int	var_in_envp(char *argv, char **envp, int ij[2])
{
	int	var_len;

	if (!argv || !envp)
		return (0);
	ij[1] = 0;
	var_len = ft_strlen(argv);
	while (envp[ij[1]])
	{
		if (check_env_match(argv, envp[ij[1]], var_len))
			return (1);
		ij[1]++;
	}
	return (0);
}
