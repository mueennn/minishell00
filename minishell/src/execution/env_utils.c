/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:30:40 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/30 19:35:58 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**prepare_command(char **full_cmd)
{
	int		i;
	int		cmd_size;
	char	**new_cmd;

	if (!full_cmd || !full_cmd[1])
		return (NULL);
	cmd_size = 0;
	while (full_cmd[cmd_size + 1])
		cmd_size++;
	new_cmd = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (i < cmd_size)
	{
		new_cmd[i] = ft_strdup(full_cmd[i + 1]);
		if (!new_cmd[i])
		{
			ft_free_array(&new_cmd);
			return (NULL);
		}
		i++;
	}
	new_cmd[i] = NULL;
	return (new_cmd);
}

int	exec_env_command(char **new_cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_free_array(&new_cmd);
		mini_perror(FORKERR, NULL, 1);
		return (1);
	}
	if (pid == 0)
	{
		execvp(new_cmd[0], new_cmd);
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(new_cmd[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		ft_free_array(&new_cmd);
		exit(127);
	}
	waitpid(pid, &status, 0);
	ft_free_array(&new_cmd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
