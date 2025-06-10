/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:27:42 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/27 19:32:38 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	mini_print_error(int err_type, char *param)
{
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (err_type == NPERM)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (err_type == NCMD)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	mini_print_error_extra(int err_type, char *param)
{
	if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == PIPENDERR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (err_type == NOT_DIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd(": not a directory\n", 2);
	}
}

void	*mini_perror(int err_type, char *param, int err)
{
	g_exit_code = err;
	if (err_type <= NCMD)
		mini_print_error(err_type, param);
	else
		mini_print_error_extra(err_type, param);
	return (NULL);
}

void	cd_error(char **str[2])
{
	DIR	*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_exit_code = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_exit_code = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		mini_perror(NDIR, str[0][1], 1);
	else if (str[0][1])
		mini_perror(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}
