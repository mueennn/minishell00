/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_prc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:06:51 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/03 12:59:44 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Execute builtin commands inside the child process
 *
 * @param prompt Pointer to the prompt structure containing shell state
 * @param n Pointer to the mini shell structure containing command information
 * @param l Index or flag indicating command position or special handling
 * @param cmd Linked list containing the command to be executed
 */
static void	child_builtin(t_prompt *prompt, t_mini *n, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_builtin(n) && n->full_cmd && n->full_path)
		execve(n->full_path, n->full_cmd, prompt->envp);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", l) && l == 3)
		g_exit_code = mini_pwd();
	else if (is_builtin(n) && n->full_cmd && !ft_strncmp(*n->full_cmd, "echo",
			l) && l == 4)
		g_exit_code = mini_echo(cmd);
	else if (is_builtin(n) && n->full_cmd && !ft_strncmp(*n->full_cmd, "env", l)
		&& l == 3)
		g_exit_code = mini_env(prompt, cmd);
}

static int	check_redirections_valid(t_mini *node)
{
	if (node->infile == -1 || node->infile == -3 || node->outfile == -1)
		return (0);
	return (1);
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_mini	*node;
	int		should_execute;

	node = cmd->content;
	should_execute = check_redirections_valid(node);
	if (node->infile != STDIN_FILENO && node->infile != -3 && node->infile
		!= -1)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		safe_close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO && node->outfile != -1)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (mini_perror(DUPERR, NULL, 1));
		safe_close(node->outfile);
		node->outfile = -1;
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (mini_perror(DUPERR, NULL, 1));
	safe_close(fd[WRITE_END]);
	if (!should_execute)
		return (NULL);
	return ("");
}

static void	*child_process_setup(t_list *cmd, int fd[2],
		int *len)
{
	t_mini	*n;
	void	*redir_result;
	int		keep_fds[4];

	n = cmd->content;
	*len = 0;
	keep_fds[0] = n->infile;
	keep_fds[1] = n->outfile;
	keep_fds[2] = fd[WRITE_END];
	keep_fds[3] = -1;
	close_all_fds(keep_fds, 1024);
	if (n->full_cmd)
		*len = ft_strlen(*n->full_cmd);
	redir_result = child_redir(cmd, fd);
	safe_close(fd[READ_END]);
	return (redir_result);
}

void	*child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_mini	*n;
	int		l;
	void	*redir_result;

	n = cmd->content;
	redir_result = child_process_setup(cmd, fd, &l);
	if (!redir_result)
	{
		g_exit_code = 1;
		ft_lstclear(&prompt->cmds, free_content);
		ft_free_array(&(prompt->envp));
		exit(g_exit_code);
	}
	child_builtin(prompt, n, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	ft_free_array(&(prompt->envp));
	exit(g_exit_code);
}
