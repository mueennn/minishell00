/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rradin-m <rradin-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:28:10 by rradin-m          #+#    #+#             */
/*   Updated: 2025/04/23 11:27:33 by rradin-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_user(t_prompt prompt)
{
	char	**user;
	char	*temp;

	user = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	if (!user || !user[0])
		return (ft_strdup("guest"));
	temp = ft_strdup(user[0]);
	ft_free_array(&user);
	return (temp);
}

char	*get_cmd_prompt(t_prompt prompt)
{
	char	*username;
	char	*result;

	username = get_user(prompt);
	if (!username)
		username = ft_strdup("guest");
	result = ft_strjoin(username, "@minishell$ ");
	free(username);
	return (result);
}
