/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:27:26 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/18 18:30:18 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	update_output(char ***array, int fd)
{
	char	**aux;
	char	*temp;
	char	*line;

	aux = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
		aux = ft_extend_array(aux, temp);
		free(temp);
	}
	ft_free_array(array);
	*array = aux;
}

void	exec_custom(char ***out, char *full, char *args, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**array;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		array = ft_split(args, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full, F_OK))
			execve(full, array, envp);
		ft_free_array(&envp);
		exit(1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(out, fd[READ_END]);
	close(fd[READ_END]);
}
