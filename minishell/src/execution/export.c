/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:30:04 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/21 18:25:36 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_single_env(const char *env)
{
	char	*equal_sign;
	char	*var_name;
	char	*var_value;
	int		j;

	equal_sign = ft_strchr(env, '=');
	if (equal_sign)
	{
		j = equal_sign - env;
		var_name = ft_substr(env, 0, j);
		var_value = ft_strdup(equal_sign + 1);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(var_name, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(var_value, 1);
		ft_putstr_fd("\"\n", 1);
		free(var_name);
		free(var_value);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((char *)env, 1);
		ft_putstr_fd("\n", 1);
	}
}

static void	print_exported_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		print_single_env(envp[i]);
		i++;
	}
}

static void	process_var_with_equal(char *arg, t_prompt *prompt)
{
	char	*equal_sign;
	int		var_len;
	char	*var_name;
	char	*var_value;

	equal_sign = ft_strchr(arg, '=');
	var_len = equal_sign - arg;
	var_name = ft_substr(arg, 0, var_len);
	var_value = ft_strdup(equal_sign + 1);
	prompt->envp = mini_setenv(var_name, var_value, prompt->envp, var_len);
	free(var_name);
	free(var_value);
}

static int	process_export_arg(char *arg, t_prompt *prompt)
{
	int	ij[2];

	ij[0] = 0;
	ij[1] = 0;
	if (is_valid_identifier(arg))
	{
		if (ft_strchr(arg, '='))
			process_var_with_equal(arg, prompt);
		else if (!var_in_envp(arg, prompt->envp, ij))
			prompt->envp = ft_extend_array(prompt->envp, arg);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_code = 1;
		return (1);
	}
}

int	mini_export(t_prompt *prompt)
{
	int		i;
	char	**argv;
	int		result;

	result = 0;
	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_arraylen(argv) < 2)
	{
		print_exported_env(prompt->envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (process_export_arg(argv[i], prompt))
			result = 1;
		i++;
	}
	return (result);
}
