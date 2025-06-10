/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:11:20 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/03 13:03:35 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	safe_close(int fd)
{
	static int	closed_fds[1024] = {0};
	int			result;

	if (fd == -1)
	{
		ft_memset(closed_fds, 0, sizeof(closed_fds));
		return (0);
	}
	if (fd <= 2)
		return (0);
	if (fd < 1024 && closed_fds[fd] == 1)
		return (0);
	if (fd < 1024)
		closed_fds[fd] = 1;
	result = close(fd);
	return (result);
}

static int	should_keep_fd_open(int fd, int *keep_open)
{
	int	j;

	if (!keep_open)
		return (0);
	j = 0;
	while (keep_open[j] != -1)
	{
		if (keep_open[j] == fd)
			return (1);
		j++;
	}
	return (0);
}

void	close_all_fds(int *keep_open, int max_fd)
{
	int	i;
	int	should_keep;

	if (max_fd <= 0)
		max_fd = 1024;
	i = 3;
	while (i < max_fd)
	{
		should_keep = should_keep_fd_open(i, keep_open);
		if (!should_keep)
			safe_close(i);
		i++;
	}
}

void	free_content(void *content)
{
	t_mini	*node;

	node = content;
	ft_free_array(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		safe_close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		safe_close(node->outfile);
	free(node);
}

void	ft_free_array(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}
