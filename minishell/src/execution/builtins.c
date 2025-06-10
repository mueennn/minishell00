/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:33:47 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/30 19:43:41 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	mini_env(t_prompt *prompt, t_list *cmd)
{
	t_mini	*node;
	char	**new_cmd;

	node = cmd->content;
	if (!node->full_cmd[1])
	{
		ft_put_array_fd(prompt->envp, 1, 1);
		return (0);
	}
	new_cmd = prepare_command(node->full_cmd);
	if (!new_cmd)
		return (1);
	return (exec_env_command(new_cmd));
}

int	mini_cd(t_prompt *p)
{
	char	**str[2];
	char	*aux;

	g_exit_code = 0;
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	aux = mini_getenv("HOME", p->envp, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_array(NULL, aux);
	free(aux);
	aux = getcwd(NULL, 0);
	str[1] = ft_extend_array(str[1], aux);
	free(aux);
	cd_error(str);
	if (!g_exit_code)
		p->envp = mini_setenv("OLDPWD", str[1][1], p->envp, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_array(str[1], aux);
	free(aux);
	p->envp = mini_setenv("PWD", str[1][2], p->envp, 3);
	ft_free_array(&str[1]);
	return (g_exit_code);
}

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	mini_echo(t_list *cmd)
{
	int		newline;
	int		i[2];
	char	**argv;
	t_mini	*node;

	i[0] = 0;
	i[1] = 0;
	newline = 1;
	node = cmd->content;
	argv = node->full_cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2)
			&& (ft_countchar(argv[i[0]], 'n') == (int)(ft_strlen(argv[i[0]])
				- 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}
