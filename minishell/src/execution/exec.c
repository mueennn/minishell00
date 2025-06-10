/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:27:50 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/02 18:29:05 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		mini_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(prompt, cmd, fd);
}

void	*check_to_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;

	n = cmd->content;
	if (cmd->next || fd[READ_END] != 0 || fd[WRITE_END] != 1)
	{
		exec_fork(prompt, cmd, fd);
		return ("");
	}
	if ((n->infile == -1 && n->infile != -3) || n->outfile == -1 || n->infile
		== -3)
	{
		g_exit_code = 1;
		return ("");
	}
	if ((n->full_path && access(n->full_path, X_OK) == 0) || is_builtin(n))
		exec_fork(prompt, cmd, fd);
	else if (!is_builtin(n) && n->full_path && !access(n->full_path, F_OK))
		g_exit_code = 126;
	else if (!is_builtin(n) && n->full_cmd)
		g_exit_code = 127;
	return ("");
}
