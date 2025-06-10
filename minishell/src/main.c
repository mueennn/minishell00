/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:01:27 by rradin-m          #+#    #+#             */
/*   Updated: 2025/05/03 12:51:17 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	mini_getpid(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_array(&p->envp);
		exit(1);
	}
	if (pid == 0)
	{
		ft_free_array(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_prompt	init_env(t_prompt prompt, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);
	str = mini_getenv("SHLVL", prompt.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);
	str = mini_getenv("PATH", prompt.envp, 4);
	if (!str)
		prompt.envp = mini_setenv("PATH",
				"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:", prompt.envp,
				4);
	free(str);
	str = mini_getenv("_", prompt.envp, 1);
	if (!str)
		prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);
	free(str);
	return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_array_dup(envp);
	g_exit_code = 0;
	mini_getpid(&prompt);
	prompt = init_env(prompt, str, argv);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt_str;
	char		*full_cmd;
	t_prompt	prompt;

	prompt = init_prompt(argv, envp);
	while (argv && argc)
	{
		safe_close(-1);
		handle_signals();
		prompt_str = get_cmd_prompt(prompt);
		if (prompt_str)
			full_cmd = readline(prompt_str);
		else
			full_cmd = readline("guest@minishell$ ");
		free(prompt_str);
		if (!validate_args(full_cmd, &prompt))
			break ;
	}
	ft_free_array(&(prompt.envp));
	exit(g_exit_code);
}
