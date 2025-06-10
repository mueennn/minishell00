/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:36:46 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/21 18:25:36 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_directory(t_mini *n, DIR *dir)
{
	if (dir)
	{
		if (ft_strchr(*n->full_cmd, '/'))
		{
			mini_perror(IS_DIR, *n->full_cmd, 126);
			g_exit_code = 126;
		}
		else
		{
			mini_perror(NCMD, *n->full_cmd, 127);
			g_exit_code = 127;
		}
		closedir(dir);
	}
}

static void	handle_path_access(t_mini *n, DIR *test_dir)
{
	if (test_dir)
	{
		mini_perror(IS_DIR, n->full_path, 126);
		g_exit_code = 126;
		closedir(test_dir);
	}
	else if (access(n->full_path, F_OK) == -1)
	{
		mini_perror(NDIR, n->full_path, 127);
		g_exit_code = 127;
	}
	else if (access(n->full_path, X_OK) == -1)
	{
		mini_perror(NPERM, n->full_path, 126);
		g_exit_code = 126;
	}
}

static void	handle_cmd_access(t_mini *n)
{
	DIR	*test_dir;

	if (!is_builtin(n) && n && n->full_path)
	{
		test_dir = opendir(n->full_path);
		handle_path_access(n, test_dir);
	}
	else if (!is_builtin(n) && n && !n->full_path)
	{
		mini_perror(NCMD, *n->full_cmd, 127);
		g_exit_code = 127;
	}
}

void	get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_mini	*n;
	DIR		*dir;

	n = cmd->content;
	dir = cmd_checks(prompt, cmd, &s, path);
	if (!n || !n->full_cmd || !n->full_cmd[0] || !n->full_cmd[0][0])
	{
		if (dir)
			closedir(dir);
		ft_free_array(&s);
		return ;
	}
	if (dir)
	{
		handle_directory(n, dir);
		ft_free_array(&s);
		return ;
	}
	handle_cmd_access(n);
	ft_free_array(&s);
}
