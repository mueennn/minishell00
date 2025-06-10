/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_hand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:27:11 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/30 19:51:47 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_mini *)cmd->content)->full_cmd;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_exit_code = mini_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_exit_code = mini_cd(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_exit_code = mini_export(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_exit_code = mini_unset(prompt);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			set_pipe(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_exit_code);
}

int	is_builtin(t_mini *n)
{
	int	l;

	if (!n->full_cmd)
		return (0);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path
			&& ft_strchr(n->full_path, '/')))
		return (0);
	l = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}
