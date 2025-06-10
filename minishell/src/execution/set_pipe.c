/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:27:58 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/02 17:56:15 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*set_pipe(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];
	t_mini	*n;

	n = cmd->content;
	get_cmd(prompt, cmd, NULL, NULL);
	if (!mini_here_fd(fd))
		return (NULL);
	exec_fork(prompt, cmd, fd);
	safe_close(fd[WRITE_END]);
	if (cmd->next && !((t_mini *)cmd->next->content)->infile)
		((t_mini *)cmd->next->content)->infile = fd[READ_END];
	else
		safe_close(fd[READ_END]);
	if (n->infile > 2)
		safe_close(n->infile);
	if (n->outfile > 2)
		safe_close(n->outfile);
	return (NULL);
}
