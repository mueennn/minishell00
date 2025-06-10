/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:55:32 by arimoham          #+#    #+#             */
/*   Updated: 2025/04/29 16:24:32 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**tokenize_args(char **args, t_prompt *prompt)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, prompt);
		args[i] = expand_path(args[i], -1, quotes, mini_getenv("HOME",
					prompt->envp, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_array_replace_in(&args, subsplit, i);
		i += ft_arraylen(subsplit) - 1;
		ft_free_array(&subsplit);
	}
	return (args);
}

static void	*parse_args(char **args, t_prompt *p)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	p->cmds = fill_nodes(tokenize_args(args, p), -1);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_exit_code = builtin(p, p->cmds, &is_exit, 0);
	while (i > 0)
	{
		waitpid(-1, &g_exit_code, 0);
		i--;
	}
	if (!is_exit && g_exit_code == 13)
		g_exit_code = 0;
	if (g_exit_code > 255)
		g_exit_code = g_exit_code / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}
	return (p);
}

void	*validate_args(char *full_cmd, t_prompt *p)
{
	char	**a;
	t_mini	*n;

	if (!full_cmd)
	{
		printf("exit\n");
		return (NULL);
	}
	if (full_cmd[0])
		add_history(full_cmd);
	a = ft_cmd_trim(full_cmd, " ");
	free(full_cmd);
	if (!a)
		return (mini_perror(QUOTE, NULL, 1), "");
	p = parse_args(a, p);
	if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = mini_setenv("_", n->full_cmd[ft_arraylen(n->full_cmd) - 1],
				p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
