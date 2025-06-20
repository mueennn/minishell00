/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:28:05 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/25 14:47:57 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_here_str(char *str[2], size_t len, char *limit, char *warn)
{
	char	*temp;

	while (g_exit_code != 130 && (!str[0] || ft_strncmp(str[0], limit, len)
			|| ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

void	*mini_here_fd(int fd[2])
{
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (NULL);
	}
	return ("");
}

int	get_here_doc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_exit_code = 0;
	if (mini_here_fd(fd) == NULL)
		return (-1);
	str[1] = get_here_str(str, 0, aux[0], aux[1]);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_exit_code == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
