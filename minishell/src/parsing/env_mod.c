/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:52:53 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/23 11:57:54 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	modify_env(char **envp, char *var, char *full_var, int n)
{
	int		i;
	char	*old_var;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], var, n) && (envp[i][n] == '='
			|| envp[i][n] == '\0'))
		{
			old_var = envp[i];
			envp[i] = ft_strdup(full_var);
			free(old_var);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	char	*full_var[2];
	int		found;

	if (n < 0)
		n = ft_strlen(var);
	full_var[0] = ft_strjoin(var, "=");
	full_var[1] = ft_strjoin(full_var[0], value);
	free(full_var[0]);
	found = modify_env(envp, var, full_var[1], n);
	if (!found)
		envp = ft_extend_array(envp, full_var[1]);
	free(full_var[1]);
	return (envp);
}
